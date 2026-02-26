/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakkoc <eakkoc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 20:26:00 by eakkoc            #+#    #+#             */
/*   Updated: 2026/02/26 20:26:01 by eakkoc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	space_check(t_cube *cube, int i, int j)
{
	int	w;

	w = ft_strlen(cube->map.maps[i]) - 1;
	if (i == 0 || i == cube->map.height - 1)
	{
		if (cube->map.maps[i][j] != '1' && cube->map.maps[i][j] != ' ')
			return (1);
	}
	if (j == 0 || j == w)
	{
		if (cube->map.maps[i][j] != '1' && cube->map.maps[i][j] != ' ')
			return (1);
	}
	return (0);
}

int	check_map_after(t_cube *cube)
{
	int	i;
	int	j;

	i = cube->map.map_start + cube->map.height;
	while (cube->lines[i])
	{
		j = 0;
		while (cube->lines[i][j])
		{
			if (cube->lines[i][j] != ' ' && cube->lines[i][j] != '\t'
				&& cube->lines[i][j] != '\r' && cube->lines[i][j] != '\n'
				&& cube->lines[i][j] != '\v' && cube->lines[i][j] != '\f')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	up_down_check(t_cube *cube)
{
	int	i;

	i = 0;
	while (cube->map.maps[0][i])
	{
		if (cube->map.maps[0][i] != '1' && cube->map.maps[0][i] != ' ')
			return (1);
		i++;
	}
	i = 0;
	while (cube->map.maps[cube->map.height - 1][i])
	{
		if (cube->map.maps[(cube->map.height) - 1][i] != '1'
			&& cube->map.maps[(cube->map.height) - 1][i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

static int	check_row(t_cube *cube, int row)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(cube->map.maps[row]);
	while (i < len)
	{
		if (space_check(cube, row, i))
			return (1);
		i++;
	}
	return (0);
}

int	check_sides(t_cube *cube)
{
	int	i;
	int	len;

	if (check_row(cube, 0) || check_row(cube, cube->map.height - 1))
		return (1);
	i = 1;
	while (i < cube->map.height - 1)
	{
		len = ft_strlen(cube->map.maps[i]);
		if (space_check(cube, i, 0) || space_check(cube, i, len - 1))
			return (1);
		i++;
	}
	return (0);
}
