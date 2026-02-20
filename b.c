// #include "a.h"
#include "cub3d.h"



void calc_values(t_cube *cube, int x, int width, t_values *values)
{
    values->cam_x = 2 * x / (double)width - 1; 
   
    values->dir_x = cos(cube->game->angle);
    values->dir_y = sin(cube->game->angle);
    // set_dir(cube->player.dir,values);
    values->plane_x = -sin(cube->game->angle) * 0.66;
    values->plane_y =  cos(cube->game->angle) * 0.66;
    values->raydir_x = values->dir_x + values->plane_x * values->cam_x;
    values->raydir_y = values->dir_y + values->plane_y * values->cam_x;
    values->delta_x = fabs(1 / values->raydir_x);
    values->delta_y = fabs(1 / values->raydir_y);
    values->map_x = (int)(cube->game->posx / 64);
    values->map_y = (int)(cube->game->posy / 64);
    values->spos_x = cube->game->posx / 64.0;
    values->spos_y = cube->game->posy / 64.0;
    if (values->raydir_x < 0)
    {
        values->step_x = -1;
        values->perp_x = (values->spos_x - values->map_x) * values->delta_x;
    }
    else
    {
        values->step_x = 1;
        values->perp_x = (values->map_x + 1 - values->spos_x) * values->delta_x;
    }
    if (values->raydir_y < 0)
    {
        values->step_y = -1;
        values->perp_y = (values->spos_y - values->map_y) * values->delta_y;
    }
    else
    {
        values->step_y = 1;
        values->perp_y = (values->map_y + 1 - values->spos_y) * values->delta_y;
    }
}

int dda_loop(t_values *values, t_game *game)
{
    int hit;
    int side;

    hit = 0;
    while (hit == 0)
    {
        if (values->perp_x < values->perp_y) 
        {
            values->perp_x += values->delta_x;
            values->map_x += values->step_x;
            side = 0;
        } 
        else 
        {
            values->perp_y += values->delta_y;
            values->map_y += values->step_y;
            side = 1;
        }
        if (game->map[values->map_y][values->map_x] == '1') 
            hit = 1;
    }
    return (side);
}

double perp_dist(t_values values, int side)
{
    double perp_dist;

    if (side == 0)
        perp_dist = values.perp_x - values.delta_x;
    else
        perp_dist = values.perp_y - values.delta_y;
    return (perp_dist);
}

void draw_line(t_game *game, int x, int start, int end)
{
    while (start < end)
    {
        mlx_pixel_put(game->mlx, game->win, x, start, 0xFF0000);
        start++;
    }
}

void set_line_h(double dist, int h, int x, t_cube *cube, t_values *values, int side)
{
    int line_h;
    int start;
    int end;

    line_h = (int)(h / dist);
    start = -line_h / 2 + h / 2;
    end = line_h / 2 + h / 2;
    if(start < 0)
        start = 0;
    if (end > h)
        end = h;
    texture(cube->game, values, side, dist, line_h, start, end, x);
    draw_ceil_floor(cube, x, start, end, h);
}

void raycast(t_cube *cube)
{
    int x;
    int h;
    int w;
    int side;
    double dist;

    x = 0;
    w = SCREENW;
    h = SCREENH;
    t_values values;
    while (x < SCREENW)
    {
        calc_values(cube, x, w, &values);
        side = dda_loop(&values, cube->game);
        dist = perp_dist(values, side);
        set_line_h(dist, h, x, cube, &values, side);
        x++;
    }
}
