/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udemirci <udemirci@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 20:25:46 by eakkoc            #+#    #+#             */
/*   Updated: 2026/02/27 04:22:10 by udemirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_path(t_cube *cube, char *path)
{
	int	len;

	len = ft_strlen(path);
	if ((path[len - 4] != '.' || path[len - 3] != 'c' || path[len - 2] != 'u'
			|| path[len - 1] != 'b'))
	{
		ft_printf("Error\nFile extension is invalid\n");
		exit(1);
	}
	cube->fd = open(path, O_RDONLY);
	if (cube->fd < 0)
	{
		ft_printf("Error\nInvalid or private file\n");
		exit(1);
	}
}

static int	count_lines(char *path)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		count++;
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

void	read_lines(t_cube *cube, char *path)
{
	int		fd;
	int		count;
	char	*line;

	count = count_lines(path);
	if (count == 0)
	{
		ft_printf("Error\nEmpty file or open error\n");
		exit(1);
	}
	cube->lines = ft_calloc(sizeof(char *), (count + 1));
	if (!cube->lines)
	{
		ft_printf("Error\nft_calloc error\n");
		exit(1);
	}
	fd = open(path, O_RDONLY);
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		cube->lines[count++] = line;
		line = get_next_line(fd);
	}
	close(fd);
}
