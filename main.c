/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakkoc <eakkoc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 20:25:58 by eakkoc            #+#    #+#             */
/*   Updated: 2026/02/26 20:50:48 by eakkoc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_identifiers(t_cube *cube)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (i < cube->map.map_start)
	{
		if (cube->lines[i][0] != '\0')
		{
			j = 0;
			while (cube->lines[i][j])
			{
				if (ft_isspace(cube->lines[i][j]))
					j++;
				else if (cube->lines[i][j] != '\0')
				{
					count++;
					break ;
				}
			}
		}
		i++;
	}
	return (count);
}

static int	get_map(t_cube *cube)
{
	int	i;

	find_map_start(cube);
	if (check_identifiers(cube) != 6)
		free_cube(cube, "Error\nUnexpected line\n");
	count_map_height(cube);
	if (map_alloc(cube))
		return (1);
	i = -1;
	while (++i < cube->map.height)
		fill_map(cube, i);
	i = -1;
	while (++i < cube->map.height)
	{
		fill_map_n(cube, i);
	}
	return (0);
}

int	map_check(t_cube *cube)
{
	if (check_map_after(cube))
		free_cube(cube, "Error\nCharacter after map\n");
	if (!locate_player(cube))
		free_cube(cube, "Error\nWrong amount of player\n");
	if (handle_space_player(cube))
		free_cube(cube, "Error\nWrong place for player\n");
	if (up_down_check(cube))
		free_cube(cube, "Error\nOpen map\n");
	if (check_sides(cube))
		free_cube(cube, "Error\nOpen map\n");
	handle_space(cube);
	return (0);
}

int	parser(t_cube *cube, char **argv)
{
	int	i;

	init_textures(cube);
	if (check_path(cube, argv[1]))
		free_cube(cube, "Error\nFile extension error\n");
	read_lines(cube, argv[1]);
	i = 0;
	while (cube->lines[i])
	{
		if (is_maps_line(cube->lines[i]))
			break ;
		if (cube->lines[i][0] == '\0')
		{
			i++;
			continue ;
		}
		texture_check(cube, cube->lines[i]);
		parse_colour(cube, cube->lines[i]);
		i++;
	}
	if (zero_check(cube))
		free_cube(cube, "Error\nWrong amount of texture or colour\n");
	get_map(cube);
	map_check(cube);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cube	cube;

	if (argc != 2)
	{
		printf("Error\nInvalid argc\n");
		return (1);
	}
	if (parser(&cube, argv))
		return (1);
	render(&cube);
	return (0);
}
