/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udemirci <udemirci@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 17:47:58 by udemirci          #+#    #+#             */
/*   Updated: 2026/02/27 01:58:34 by udemirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_wall(double x, double y, char **map)
{
	int	mapx;
	int	mapy;

	mapx = (int)((x) / 64);
	mapy = (int)((y) / 64);
	if (map[mapy][mapx] == '1')
		return (1);
	return (0);
}

void	move_backward(t_game *game)
{
	double	newx;
	double	newy;

	newx = game->posx - cos(game->angle) * 1.5;
	newy = game->posy - sin(game->angle) * 1.5;
	if (!is_wall(newx, game->posy, game->map))
		game->posx = newx;
	if (!is_wall(game->posx, newy, game->map))
		game->posy = newy;
}

void	move_forward(t_game *game)
{
	double	newx;
	double	newy;

	newx = game->posx + cos(game->angle) * 1.5;
	newy = game->posy + sin(game->angle) * 1.5;
	if (!is_wall(newx, game->posy, game->map))
		game->posx = newx;
	if (!is_wall(game->posx, newy, game->map))
		game->posy = newy;
}

void	move_left(t_game *game)
{
	double	newx;
	double	newy;

	newx = game->posx + cos(game->angle - M_PI / 2.0) * 1.5;
	newy = game->posy + sin(game->angle - M_PI / 2.0) * 1.5;
	if (!is_wall(newx, game->posy, game->map))
		game->posx = newx;
	if (!is_wall(game->posx, newy, game->map))
		game->posy = newy;
}

void	move_right(t_game *game)
{
	double	newx;
	double	newy;

	newx = game->posx + cos(game->angle + M_PI / 2.0) * 1.5;
	newy = game->posy + sin(game->angle + M_PI / 2.0) * 1.5;
	if (!is_wall(newx, game->posy, game->map))
		game->posx = newx;
	if (!is_wall(game->posx, newy, game->map))
		game->posy = newy;
}
