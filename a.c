#include "mlx/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <unistd.h>
#include "cub3d.h"


int is_wall(double x, double y, char **map)
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

    if (!is_wall(newx, game->posy, game->map))
        game->posx = newx;
    if (!is_wall(game->posx, newy, game->map))
        game->posy = newy;
}


void move_forward(t_game *game)
{
    double newx = game->posx + cos(game->angle) * 10;
    double newy = game->posy + sin(game->angle) * 10;

    if (!is_wall(newx, game->posy, game->map))
        game->posx = newx;
    if (!is_wall(game->posx, newy, game->map))
        game->posy = newy;
}


int key_hook(int keycode, void *param)
{
    t_cube *cube = (t_cube *)param;

    if (keycode == 13)
        move_forward(cube->game);
    if (keycode == 1)
        move_backward(cube->game);
    if (keycode == 0)
        rotate_left(cube->game);
    if (keycode == 2)
        rotate_right(cube->game);
    if (keycode == 53)
        exit(0);
    start_raycasting(cube);
    return 0;
}

void set_dir(char dir, t_game *game)
{
    if (dir == 'E')
        game->angle = 0.0;
    else if (dir == 'S')
        game->angle = M_PI / 2.0;
    else if (dir == 'W')
        game->angle = M_PI;
    else
        game->angle = 3.0 * M_PI / 2.0;
}


void start_raycasting(t_cube *cube)
{
    cube->game->img = mlx_new_image(cube->game->mlx, SCREENW, SCREENH);
    cube->game->addr = (int *)mlx_get_data_addr(cube->game->img, 
        &cube->game->bits_per_pixel, &cube->game->line_length, &cube->game->endian);
    raycast(cube);
    mlx_put_image_to_window(cube->game->mlx, cube->game->win, cube->game->img, 0, 0);
    mlx_destroy_image(cube->game->mlx, cube->game->img);
}


void render(t_cube *cube)
{
    cube->game = malloc(sizeof(t_game));
    cube->game->mlx = mlx_init();
    cube->game->win = mlx_new_window(cube->game->mlx, SCREENW, SCREENH, "cub3D");
    cube->map.maps[cube->player.x][cube->player.y] = '0';
    cube->game->map = cube->map.maps;
    cube->game->posx = cube->player.y * 64 + 32;
    cube->game->posy = cube->player.x * 64 + 32;
    cube->game->tex_h = 64;
    cube->game->tex_w = 64;
    set_dir(cube->player.dir, cube->game);
    load_textures(cube);
    start_raycasting(cube);
    mlx_key_hook(cube->game->win, key_hook, cube);
    mlx_loop(cube->game->mlx);   
}

