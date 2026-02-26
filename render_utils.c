/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udemirci <udemirci@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 17:41:06 by udemirci          #+#    #+#             */
/*   Updated: 2026/02/26 20:15:42 by udemirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_game(t_cube *cube, char *msg)
{
	if (cube->game->mlx)
	{
		destroy_textures(cube);
		if (cube->game->win)
			mlx_destroy_window(cube->game->mlx, cube->game->win);
		mlx_destroy_display(cube->game->mlx);
		free(cube->game->mlx);
	}
	free(cube->game);
	free_cube(cube, msg);
}

int	close_window(t_cube *cube)
{
	free_game(cube, "");
	return (0);
}

double	perp_dist(t_values values, int side)
{
	double	perp_dist;

	if (side == 0)
		perp_dist = values.perp_x - values.delta_x;
	else
		perp_dist = values.perp_y - values.delta_y;
	return (perp_dist);
}

void	draw_ceil_floor(t_cube *cube, int x, int start, int end)
{
	int	y;

	y = 0;
	while (y < start)
	{
		cube->game->addr[y * (cube->game->line_length / 4)
			+ x] = cube->text.ceiling;
		y++;
	}
	y = end;
	while (y < SCREENH)
	{
		cube->game->addr[y * (cube->game->line_length / 4)
			+ x] = cube->text.floor;
		y++;
	}
}
