/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakkoc <eakkoc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 20:26:13 by eakkoc            #+#    #+#             */
/*   Updated: 2026/02/26 20:55:33 by eakkoc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_ext(t_cube *cube, char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len < 4 || ft_strncmp(line + len - 4, ".xpm", 4) != 0)
	{
		free(line);
		free_cube(cube, "Error\nTexture extension error\n");
	}
}

char	*texture_path(t_cube *cube, char *path, char *set)
{
	char	*trim;
	char	*line;
	int		i;
	int		len;

	trim = ft_strtrim(path, set);
	if (!trim)
		return (NULL);
	i = 0;
	while (trim[i] && ft_isspace(trim[i]))
		i++;
	line = ft_strdup(trim + i);
	free(trim);
	if (!line)
		return (NULL);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[--len] = '\0';
	check_ext(cube, line);
	return (line);
}

static void	assign_texture(t_cube *cube, char **target, char *line, char *id)
{
	if (*target != NULL)
		free_cube(cube, "Error\nTexture has been defined\n");
	*target = texture_path(cube, line, id);
}

int	texture_check(t_cube *cube, char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!ft_strncmp((line + i), "SO ", 3))
		assign_texture(cube, &cube->text.so, line + i, "SO");
	else if (!ft_strncmp((line + i), "NO ", 3))
		assign_texture(cube, &cube->text.no, line + i, "NO");
	else if (!ft_strncmp((line + i), "WE ", 3))
		assign_texture(cube, &cube->text.we, line + i, "WE");
	else if (!ft_strncmp((line + i), "EA ", 3))
		assign_texture(cube, &cube->text.ea, line + i, "EA");
	else
		return (1);
	return (0);
}

int	zero_check(t_cube *cube)
{
	if (!cube->text.no || !cube->text.so || !cube->text.we || !cube->text.ea
		|| (cube->text.f_check != 1) || (cube->text.c_check != 1))
		return (1);
	return (0);
}
