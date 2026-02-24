/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakkoc <eakkoc@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-13 13:22:36 by eakkoc            #+#    #+#             */
/*   Updated: 2025-04-13 13:22:36 by eakkoc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_buffer(int fd, char *buf, char *backup)
{
	int		read_line;
	char	*temp_backup;

	read_line = 1;
	while (read_line != 0)
	{
		read_line = read(fd, buf, BUFFER_SIZE);
		if (read_line == -1)
		{
			return (NULL);
		}
		if (read_line == 0)
			break ;
		buf[read_line] = '\0';
		if (!backup)
			backup = ft_strdup("");
		temp_backup = backup;
		backup = ft_strjoin(temp_backup, buf);
		free(temp_backup);
		temp_backup = NULL;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (backup);
}

static char	*update_backup(char *line)
{
	size_t	count;
	char	*new_backup;

	count = 0;
	while (line[count] != '\n' && line[count] != '\0')
		count++;
	if (line[count] == '\0')
		return (NULL);
	new_backup = ft_substr(line, count + 1, ft_strlen(line) - count);
	if (!new_backup)
		return (NULL);
	if (*new_backup == '\0')
	{
		free(new_backup);
		new_backup = NULL;
		return (NULL);
	}
	line[count + 1] = '\0';
	return (new_backup);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	static char	*backup = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	line = read_buffer(fd, buf, backup);
	free(buf);
	buf = NULL;
	if (!line)
	{
		if (backup)
		{
			free(backup);
			backup = NULL;
		}
		line = NULL;
		return (NULL);
	}
	backup = update_backup(line);
	return (line);
}
