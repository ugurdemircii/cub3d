#include "cub3d.h"

// Helper function to find newline
static int	has_newline(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

// Helper function to get string length
static int	ft_strlen_gnl(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

// Helper function to join two strings
static char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*result;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
	{
		result = malloc(ft_strlen_gnl(s2) + 1);
		if (!result)
			return (NULL);
		i = -1;
		while (s2[++i])
			result[i] = s2[i];
		result[i] = '\0';
		return (result);
	}
	result = malloc(ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1);
	if (!result)
		return (NULL);
	i = -1;
	while (s1[++i])
		result[i] = s1[i];
	j = 0;
	while (s2[j])
		result[i++] = s2[j++];
	result[i] = '\0';
	free(s1);
	return (result);
}

// Extract one line from buffer
static char	*extract_line(char *buffer)
{
	char	*line;
	int		i;

	if (!buffer || !buffer[0])
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

// Remove extracted line from buffer
static char	*clean_buffer(char *buffer)
{
	char	*new_buffer;
	int		i;
	int		j;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = malloc(ft_strlen_gnl(buffer) - i + 1);
	if (!new_buffer)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	new_buffer[j] = '\0';
	free(buffer);
	return (new_buffer);
}

// Main get_next_line function
char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*read_buf;
	char		*line;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_buf = malloc(BUFFER_SIZE + 1);
	if (!read_buf)
		return (NULL);
	bytes_read = 1;
	while (!has_newline(buffer) && bytes_read > 0)
	{
		bytes_read = read(fd, read_buf, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(read_buf);
			return (NULL);
		}
		read_buf[bytes_read] = '\0';
		buffer = ft_strjoin_gnl(buffer, read_buf);
	}
	free(read_buf);
	line = extract_line(buffer);
	buffer = clean_buffer(buffer);
	return (line);
}