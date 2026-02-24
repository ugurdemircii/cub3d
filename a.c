#include "mlx/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <unistd.h>
#include "cub3d.h"

int close_window(t_cube *cube)
{
    exit(0);
    return (0);
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

void init_game_values(t_cube *cube)
{
    cube->game = malloc(sizeof(t_game));
    if (cube->game == NULL)
        exit(printf("Error\nmalloc failed\n"));
    cube->game->mlx = mlx_init();
    cube->game->win = mlx_new_window(cube->game->mlx, SCREENW, SCREENH, "cub3D");
    if (cube->game->mlx == NULL || cube->game->win == NULL)
        exit(printf("Error\nmlx_init or mlx_new_window failed\n"));
    cube->game->w_key = 0;
    cube->game->a_key = 0;
    cube->game->s_key = 0;
    cube->game->d_key = 0;
    cube->game->left_key = 0;
    cube->game->right_key = 0;
    cube->map.maps[cube->player.x][cube->player.y] = '0';
    cube->game->map = cube->map.maps;
    cube->game->posx = cube->player.y * 64 + 32;
    cube->game->posy = cube->player.x * 64 + 32;
    cube->game->tex_h = 64;
    cube->game->tex_w = 64;
}


void render(t_cube *cube)
{
    init_game_values(cube);
    set_dir(cube->player.dir, cube->game);
    load_textures(cube);
    start_raycasting(cube);
    mlx_hook(cube->game->win, 2, 1L<<0, key_press, cube);
    mlx_hook(cube->game->win, 3, 1L<<1, key_release, cube);
    mlx_loop_hook(cube->game->mlx, game_loop, cube);
    mlx_hook(cube->game->win, 17, 0, close_window, cube);
    mlx_loop(cube->game->mlx);   
}

