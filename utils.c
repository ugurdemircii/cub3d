/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udemirci <udemirci@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 20:26:19 by eakkoc            #+#    #+#             */
/*   Updated: 2026/02/27 02:05:04 by udemirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_maps_line(char *line)
{
	int	i;
	int	w;

	if (!line || *line == '\0')
		return (0);
	i = 0;
	w = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			break ;
		if (line[i] == '1')
			w = 1;
		else if (line[i] != '0' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W' && line[i] != ' ')
			return (0);
		i++;
	}
	return (w);
}

static int	is_valid_map_char(char c)
{
	return (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ' || c == '\n');
}

int	is_map_line(char *line)
{
	int	i;
	int	has_wall;

	i = 0;
	has_wall = 0;
	while (line[i] == ' ')
		i++;
	while (line[i])
	{
		if (!is_valid_map_char(line[i]))
			return (0);
		if (line[i] == '1')
			has_wall = 1;
		i++;
	}
	return (has_wall);
}
