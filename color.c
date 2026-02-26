/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakkoc <eakkoc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 20:25:42 by eakkoc            #+#    #+#             */
/*   Updated: 2026/02/26 21:26:57 by eakkoc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	colour_analysis(char **colour)
{
	long long	value;
	int			j;
	int			k;

	j = -1;
	while (colour[++j])
	{
		k = -1;
		while (colour[j][++k])
		{
			if ((!ft_isdigit(colour[j][k])) && (!ft_isspace(colour[j][k])))
				return (1);
		}
	}
	j = -1;
	while (++j < 3)
	{
		if (colour[j][0] == '\n')
			return (1);
		value = ft_atoi(colour[j]);
		if (value < 0 || value > 255)
			return (1);
	}
	return (0);
}

static unsigned long	add_colour(char **colour)
{
	unsigned long	result;
	int				r;
	int				g;
	int				b;

	r = ft_atoi(colour[0]);
	g = ft_atoi(colour[1]);
	b = ft_atoi(colour[2]);
	result = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return (result);
}

void	assign_colour_values(t_cube *cube, char type)
{
	int	k;

	k = 0;
	if (!cube->text.colour[0] || !cube->text.colour[1] || !cube->text.colour[2])
		free_cube(cube, "Error\nMissing colour part\n");
	while (ft_isspace(cube->text.colour[2][k]))
		k++;
	if (cube->text.colour[2][k] == '\0')
		free_cube(cube, "Error\nMissing colour part\n");
	if (colour_analysis(cube->text.colour))
		free_cube(cube, "Error\nInvalid rgb value\n");
	if (type == 'F')
	{
		cube->text.f_check++;
		cube->text.floor = add_colour(cube->text.colour);
	}
	else if (type == 'C')
	{
		cube->text.c_check++;
		cube->text.ceiling = add_colour(cube->text.colour);
	}
	free_colour(cube);
}

void	process_colour_string(t_cube *cube, char *str, char type)
{
	char	*trimmed;
	int		count;
	int		j;

	count = 0;
	j = -1;
	trimmed = ft_strtrim(str, " ");
	while (trimmed[++j])
	{
		if (trimmed[j] == ',')
			count++;
	}
	cube->text.colour = ft_split(trimmed, ',');
	free(trimmed);
	if (count != 2 || !cube->text.colour)
		free_cube(cube, "Error\nComma error in colour\n");
	assign_colour_values(cube, type);
}

int	parse_colour(t_cube *cube, char *line)
{
	int	i;

	i = 0;
	cube->text.colour = NULL;
	while (ft_isspace(line[i]))
		i++;
	if ((line[i] == 'F' || line[i] == 'C') && ft_isspace(line[i + 1]))
		process_colour_string(cube, line + i + 1, line[i]);
	return (0);
}
