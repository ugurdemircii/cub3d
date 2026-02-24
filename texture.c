#include "cub3d.h"


void load_textures(t_cube *cube)
{
    int bpp;
    int size_line;
    int endian;

    cube->game->no = mlx_xpm_file_to_image(cube->game->mlx, cube->text.no, &cube->game->tex_w, &cube->game->tex_h);
    if (!cube->game->no)
        exit(printf("Error\nNO texture error! (%s)\n", cube->text.no));
    cube->game->no_data = (int *)mlx_get_data_addr(cube->game->no, &bpp, &size_line, &endian);
    cube->game->so = mlx_xpm_file_to_image(cube->game->mlx, cube->text.so, &cube->game->tex_w, &cube->game->tex_h);
    if (!cube->game->so)
        exit(printf("Error\nSO texture error! (%s)\n", cube->text.so));
    cube->game->so_data = (int *)mlx_get_data_addr(cube->game->so, &bpp, &size_line, &endian);
    cube->game->we = mlx_xpm_file_to_image(cube->game->mlx, cube->text.we, &cube->game->tex_w, &cube->game->tex_h);
    if (!cube->game->we)
        exit(printf("Error\nWE texture error! (%s)\n", cube->text.we));
    cube->game->we_data = (int *)mlx_get_data_addr(cube->game->we, &bpp, &size_line, &endian);
    cube->game->ea = mlx_xpm_file_to_image(cube->game->mlx, cube->text.ea, &cube->game->tex_w, &cube->game->tex_h);
    if (!cube->game->ea)
        exit(printf("Error\nEA texture error! (%s)\n", cube->text.ea));
    cube->game->ea_data = (int *)mlx_get_data_addr(cube->game->ea, &bpp, &size_line, &endian);
}

void draw_texture_line(t_game *game, int *tex_data, int x, t_values *values)
{
    int		y;
    int		index;
    unsigned int	color;
    double	step;
    double	tex_pos;

    y = values->start;
    step = 64.0 / values->line_h;
    tex_pos = (values->start - SCREENH / 2 + values->line_h / 2) * step;
    while (y < values->end)
    {
        index = (int)tex_pos % 64;
        tex_pos += step;
        color = tex_data[64 * index + values->selected_x];
        game->addr[y * (game->line_length / 4) + x] = color;
        y++;
    }
}

int *get_current_texture(t_game *game, t_values *values, int side)
{
    if (side == 0)
    {
        if (values->raydir_x > 0)
            return (game->ea_data);
        return (game->we_data);
    }
    if (values->raydir_y > 0)
        return (game->so_data);
    return (game->no_data);
}


void texture(t_game *game, t_values *values, double perp_dist)
{
    double	hit_point;
    int		selected_x;
    int		*current_text;

    current_text = get_current_texture(game, values, values->side);
    if (values->side == 0)
        hit_point = values->spos_y + perp_dist * values->raydir_y;
    else
        hit_point = values->spos_x + perp_dist * values->raydir_x;
    hit_point -= floor(hit_point);
    selected_x = (int)(hit_point * 64.0);
    if ((values->side == 0 && values->raydir_x < 0) || (values->side == 1 && values->raydir_y > 0))
        selected_x = 64 - selected_x - 1;
    values->selected_x = selected_x % 64;
    draw_texture_line(game, current_text, values->x, values);
}