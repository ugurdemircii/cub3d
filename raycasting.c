/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakkoc <eakkoc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 17:51:29 by udemirci          #+#    #+#             */
/*   Updated: 2026/02/26 22:16:33 by eakkoc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_dir(char dir, t_game *game)
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

void	start_raycasting(t_cube *cube)
{
	cube->game->img = mlx_new_image(cube->game->mlx, SCREENW, SCREENH);
	cube->game->addr = (int *)mlx_get_data_addr(cube->game->img,
			&cube->game->bits_per_pixel, &cube->game->line_length,
			&cube->game->endian);
	raycast(cube);
	mlx_put_image_to_window(cube->game->mlx, cube->game->win, cube->game->img,
		0, 0);
	mlx_destroy_image(cube->game->mlx, cube->game->img);
}

void	init_game_values(t_cube *cube)
{
	cube->game = ft_calloc(sizeof(t_game), 1);
	cube->game->mlx = NULL;
	cube->game->win = NULL;
	if (cube->game == NULL)
		free_cube(cube, "Error\nft_calloc failed\n");
	cube->game->mlx = mlx_init();
	if (cube->game->mlx == NULL)
		free_game(cube, "Error\nmlx_init failed\n");
	load_textures(cube);
	cube->game->win = mlx_new_window(cube->game->mlx, SCREENW, SCREENH,
			"cub3D");
	if (cube->game->win == NULL)
		free_game(cube, "Error\nWin error\n");
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

void	render(t_cube *cube)
{
	cube->game = NULL;
	init_game_values(cube);
	set_dir(cube->player.dir, cube->game);
	start_raycasting(cube);
	mlx_hook(cube->game->win, 2, 1L << 0, key_press, cube);
	mlx_hook(cube->game->win, 3, 1L << 1, key_release, cube);
	mlx_loop_hook(cube->game->mlx, game_loop, cube);
	mlx_hook(cube->game->win, 17, 0, close_window, cube);
	mlx_loop(cube->game->mlx);
}
