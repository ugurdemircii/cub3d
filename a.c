#include "a.h"
#include "mlx/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <unistd.h>

// typedef struct s_game
// {
//     int posx;
//     int posy;
//     double angle;
//     void *mlx;
//     void *win;
// }t_game;

char *map[] = {
    "1111111111",
    "1000000001",
    "1000000001",
    "1001000001",
    "1000000001",
    "1000000001",
    "1111111111",
    NULL
};


void draw_player(void *mlx, void *win, int cx, int cy)
{
    int r = 6; 
    int y = -r;
    int color = 0x00FF00; 

    while (y <= r)
    {
        int x = -r;
        while (x <= r)
        {
            if (x * x + y * y <= r * r)
                mlx_pixel_put(mlx, win, cx + x, cy + y, color);
            x++;
        }
        y++;
    }
}

void draw_ray_to_hit(void *mlx, void *win, int beginx, int beginy, double endx, double endy)
{
    double deltax;
    double deltay;
    double pixelx;
    double pixely;
    int pixels;

    endx *= 64;
    endy *= 64;
    deltax = endx - beginx;
    deltay = endy - beginy;
    pixelx = beginx;
    pixely = beginy;
    pixels = sqrt((deltax * deltax) + (deltay * deltay));
    deltax /= pixels;
    deltay /= pixels;
    while (pixels)
    {
        mlx_pixel_put(mlx, win, (int)pixelx, (int)pixely, 0xFF0000);
        pixelx += deltax;
        pixely += deltay;
        pixels--;
    }
}


void distances(int posx, int posy, void *mlx, void *win, double angle)
{
    double pos_x;
    double pos_y;
    int mapx;
    int mapy;
    // double angle;
    double raydirx;
    double raydiry;
    double deltax;
    double deltay;
    int stepx;
    int stepy;
    double sidedistx; 
    double sidedisty;

    // angle = M_PI / 6 + 0.3;

    raydirx = cos(angle);
    raydiry = -sin(angle);
    pos_x = (double)posx / 64;
    pos_y = (double)posy / 64;
    mapx = (int)posx / 64;
    mapy = (int)posy / 64;
    deltax = fabs(1 / raydirx);
    deltay = fabs(1 / raydiry);
    if (raydirx < 0) 
    {
        stepx = -1;
        sidedistx = (pos_x - mapx) * deltax;
    } 
    else 
    {
        stepx = 1;
        sidedistx = (mapx + 1.0 - pos_x) * deltax;
    }

    if (raydiry < 0) 
    {
        stepy = -1;
        sidedisty = (pos_y - mapy) * deltay;
    } 
    else 
    {
        stepy = 1;
        sidedisty = (mapy + 1.0 - pos_y) * deltay;
    }
    printf("-----------------\n");
    printf("player pos  %f %f\n",pos_x,pos_y);
    printf("ray  pos   %d %d\n",mapx,mapy);
    printf("ray dir x  y  %f %f \n",raydirx, raydiry);
    printf("delta x y %f %f \n",deltax, deltay);
    int hit = 0; 
    int side;
    int step_count = 0;

    while (!hit) 
    {
        step_count++;
        if (sidedistx < sidedisty) 
        {
            sidedistx += deltax;
            mapx += stepx;
            side = 0;
        } 
        else 
        {
            sidedisty += deltay;
            mapy += stepy;
            side = 1;
        }
        printf("Step %d: map=(%d,%d) sideDistX=%f sideDistY=%f side=%d\n",
               step_count, mapx, mapy, sidedistx, sidedisty, side);
        printf("-----------------\n");
        if (map[mapy][mapx] == '1')
        {
            hit = 1;
            double hitX;
            double hitY;

            if (side == 0)
            {
                if (stepx > 0)
                    hitX = mapx;
                else
                    hitX = mapx + 1.0;

                hitY = pos_y + (hitX - pos_x) * (raydiry / raydirx);
            }
            else
            {
                if (stepy > 0)
                    hitY = mapy;
                else
                    hitY = mapy + 1.0;
                hitX = pos_x + (hitY - pos_y) * (raydirx / raydiry);
            }
            draw_ray_to_hit(mlx, win, posx, posy, hitX, hitY);
        }
    }   
}


void multiple_ray(void *mlx, void *win, int posx, int posy, double angle)
{
    int ray_count = 500;
    int i = 0;
    double first_ray = angle - 0.3;
    double last_ray  = angle + 0.3;
    double angle_step = (last_ray - first_ray) / ray_count;

    while (i < ray_count)
    {
        double ray_angle = first_ray + i * angle_step;
        distances(posx, posy, mlx, win, ray_angle);
        i++;
    }
}



void draw_ray(void *mlx, void *win, int player_x, int player_y, double angle)
{
    double x;
    double y;
    double rx;
    double ry;

    rx = cos(angle);
    ry = sin(angle);
    x = player_x;
    y = player_y;
    while (true)
    {
        mlx_pixel_put(mlx, win, (int)x, (int)y, 0xFF0000);
        x += rx;
        y -= ry;
        if ((int)x % 64 == 0 || (int)y % 64 == 0)
            draw_player(mlx, win, (int)x, (int)y);
        if ((int)x >= 640 || (int)y >= 448)
            break ;
    }
}


void draw_lines(void *mlx, void *win)
{
    int i = 0;
    int j = 0;
    while (i <= 640)
    {
        while (j <= 448)
        {
            mlx_pixel_put(mlx, win, i, j, 0xFF);
            j += 1;
        }
        j = 0;
        i += 64;
    }
    i = 0;
    while (j <= 448)
    {
        while (i <= 640)
        {
            mlx_pixel_put(mlx, win, i, j, 0xFF);
            i += 1;
        }
        i = 0;
        j += 64;
    }
}

void draw_square(char *map[], void *mlx, void *win)
{
    int x;
    int y;
    int i;
    int j;

    j = 0;
    i = 0;
    x = 0;
    y = 0;
    while (y < 7)
    {
        while (x < 10)
        {
            j = 0;
            if (map[y][x] == '1')
            {
                while (j < 64)
                {
                    while (i < 64)
                    {
                        mlx_pixel_put(mlx, win, x * 64 + i, y * 64 + j, 0xFFFFFF);
                        i++;
                    }
                    j++;
                    i = 0;
                }
                x++;
            }
            else
                x++;
        }
        x = 0;
        printf("salkdflka\n");
        fflush(stdout);
        y++;
    }
}

int is_wall(double x, double y)
{
    int mapx = (int)((x) / 64);
    int mapy = (int)((y) / 64);

    if (map[mapy][mapx] == '1')
        return 1;
    return 0;
}

void rotate_left(t_game *game)
{
    game->angle -= 0.2;
}

void rotate_right(t_game *game)
{
    game->angle += 0.2;
}

void move_backward(t_game *game)
{
    double newx = game->posx - cos(game->angle) * 10;
    double newy = game->posy - sin(game->angle) * 10;

    if (!is_wall(newx, game->posy))
        game->posx = newx;
    if (!is_wall(game->posx, newy))
        game->posy = newy;
}


void move_forward(t_game *game)
{
    double newx = game->posx + cos(game->angle) * 10;
    double newy = game->posy + sin(game->angle) * 10;

    if (!is_wall(newx, game->posy))
        game->posx = newx;
    if (!is_wall(game->posx, newy))
        game->posy = newy;
}


int key_hook(int keycode, void *param)
{
    t_game *game = (t_game *)param;

    if (keycode == 13)
        move_forward(game);
    if (keycode == 1)
        move_backward(game);
    if (keycode == 0)
        rotate_left(game);
    if (keycode == 2)
        rotate_right(game);
    if (keycode == 53)
        exit(0);

    mlx_clear_window(game->mlx, game->win);
    // draw_square(map, game->mlx, game->win);
    // draw_lines(game->mlx, game->win);
    // draw_player(game->mlx, game->win, game->posx, game->posy);
    // multiple_ray(game->mlx, game->win, game->posx, game->posy, game->angle);
    // raycast(game);

    return 0;
}


int main()
{
    t_game game;

    double angle = M_PI / 4;
    int win_x = 640;
    int win_y = 448;
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, win_x, win_y, "cub3d");
    // draw_square(map, mlx, win);
    // draw_lines(mlx, win);
    // draw_player(mlx, win, 145, 370);
    game.posx = 320;
    game.posy = 448;
    game.angle = M_PI / 2;
    game.mlx = mlx;
    game.win = win;
    game.map = map;
    // draw_ray(mlx, win, 145, 370, angle);
    // draw_ray(mlx, win, 145, 370, M_PI / 6 - 0.3);
    // draw_ray(mlx, win, 145, 370, M_PI / 6);
    // draw_ray(mlx, win, 145, 370, M_PI / 6 + 0.3);
    // multiple_ray(mlx, win, 145, 370, M_PI / 6);
    // distances(145, 370, mlx, win, angle);
    raycast(&game);
    // mlx_key_hook(win, key_hook, &game);
    mlx_loop(mlx);   
}