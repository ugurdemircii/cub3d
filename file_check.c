#include "cub3d.h"

int check_path(t_cube *cube, char *path)
{
    int	len;
    
    len = ft_strlen(path);
    if ((path[len - 4] != '.' || path[len - 3] != 'c'
        || path[len - 2] != 'u'
        || path[len - 1] != 'b'))
            return (1);
    
    cube->fd = open(path,O_RDONLY);
    
    if (cube->fd < 0)
    {
        close(cube->fd);
        return 1;
    }
    return 0;
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
	int		i;
	int		count;
	char	*line;

	count = count_lines(path);
	if (count == 0)
		free_cube(cube, "Empty file or open error");
	cube->lines = ft_calloc(sizeof(char *), (count + 1));
	if (!cube->lines)
		free_cube(cube, "ft_calloc error");
	fd = open(path, O_RDONLY);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		cube->lines[i++] = line;
		line = get_next_line(fd);
	}
	close(fd);
}

// void read_lines(t_cube *cube, char *path)
// {
//     int fd;
//     int i;
//     char *line;

//     fd = open(path,O_RDONLY);
//     i = 0;
//     line = get_next_line(fd);
//     while(line)
//     {
//         free(line);
//         i++;
//         line = get_next_line(fd);
//     }
//     free(line);
//     close(fd);
//     if (!i)
//         free_cube(cube, "Empty file");
//     cube->lines = ft_calloc(sizeof(char *)* (i + 1), 1);
//     if (!cube->lines)
//         free_cube(cube, "ft_calloc error");
//     fd = open(path,O_RDONLY);
//     i = 0;
//     while((line = get_next_line(fd))!=NULL)
//     {
//         cube->lines[i] = line;
//         i++;
//     }
//     cube->lines[i] = NULL;
// }

