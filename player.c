/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakkoc <eakkoc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 20:26:06 by eakkoc            #+#    #+#             */
/*   Updated: 2026/02/26 20:26:07 by eakkoc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	locate_player(t_cube *cube)
{
	int	i;
	int	j;
	int	player;

	i = -1;
	player = 0;
	while (++i < cube->map.height)
	{
		j = -1;
		while (++j < (int)ft_strlen(cube->map.maps[i]))
		{
			if (cube->map.maps[i][j] == 'N' || cube->map.maps[i][j] == 'S'
				|| cube->map.maps[i][j] == 'E' || cube->map.maps[i][j] == 'W')
			{
				++player;
				cube->player.x = i;
				cube->player.y = j;
				cube->player.dir = cube->map.maps[i][j];
			}
		}
	}
	if (player != 1)
		return (0);
	return (player);
}

int	handle_space_player(t_cube *cube)
{
	int	x;
	int	y;

	x = cube->player.x;
	y = cube->player.y;
	if (x > 0 && (cube->map.n_maps[x - 1][y] == ' ' || cube->map.n_maps[x
			- 1][y] == '\n'))
		return (1);
	if (x < cube->map.height - 1 && (cube->map.n_maps[x + 1][y] == ' '
		|| cube->map.n_maps[x + 1][y] == '\n'))
		return (1);
	if (y > 0 && (cube->map.n_maps[x][y - 1] == ' '
		|| cube->map.n_maps[x][y - 1] == '\n'))
		return (1);
	if ((cube->map.n_maps[x][y + 1] == ' '
		|| cube->map.n_maps[x][y + 1] == '\n'))
		return (1);
	return (0);
}
