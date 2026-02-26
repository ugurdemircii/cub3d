/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakkoc <eakkoc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 20:26:10 by eakkoc            #+#    #+#             */
/*   Updated: 2026/02/26 20:55:09 by eakkoc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isspace(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

static int	is_invalid_zero(char **map, int height, int i, int j)
{
	if (i - 1 < 0 || map[i - 1][j] == '\0' || map[i - 1][j] == ' ')
		return (1);
	if (i + 1 >= height || map[i + 1][j] == '\0' || map[i + 1][j] == ' ')
		return (1);
	if (j - 1 < 0 || map[i][j - 1] == '\0' || map[i][j - 1] == ' ')
		return (1);
	if (map[i][j + 1] == '\0' || map[i][j + 1] == ' ')
		return (1);
	return (0);
}

static void	process_space(t_cube *cube, int i, int j)
{
	if (cube->map.maps[i][j] == '0')
	{
		if (is_invalid_zero(cube->map.maps, cube->map.height, i, j))
			free_cube(cube, "Error\nMap is invalid\n");
	}
}

void	handle_space(t_cube *cube)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (i < cube->map.height)
	{
		k = ft_strlen(cube->map.maps[i]);
		j = 0;
		while (j < k)
		{
			process_space(cube, i, j);
			j++;
		}
		i++;
	}
}
