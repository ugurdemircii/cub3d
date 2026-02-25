#include "cub3d.h"

// char *texture_path(t_cube *cube, char *path, char *set)
// {
//     char *trim;
//     char *line;
//     int   len;
//     int i;

//     i = -1;
//     trim = ft_strtrim(path, set);
//     if (!trim)
//         return NULL;
//     while (ft_isspace(trim[++i]))
//         ;
//     line = ft_strdup(trim + i);
//     free(trim);
//     if (!line)
//         return NULL;
//     len = ft_strlen(line);
//     if (len > 0 && line[len - 1] == '\n')
//     {
//         line[len - 1] = '\0';
//         len--;
//     }
//     if (len < 4 || line[len - 4] != '.' || line[len - 3] != 'x' ||
//         line[len - 2] != 'p' || line[len - 1] != 'm')
//     {
//         free(line);
//         free_cube(cube, "Invalid texture");
//     }
//     return line;
// }

static void	check_ext(t_cube *cube, char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len < 4 || ft_strncmp(line + len - 4, ".xpm", 4) != 0)
	{
		free(line);
		free_cube(cube, "Texture error");
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
		free_cube(cube, "Texture daha önce tanımlanmış");
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

// int texture_check(t_cube *cube,char *line)
// {
//     int i;

//     i = -1;
//     if (!line)
//         return (1);

//     while (ft_isspace(line[++i]))
//         ;
//     if (!ft_strncmp((line + i), "SO ", 3))
//     {

//         if (cube->text.so == NULL)
//             cube->text.so = texture_path(cube, line + i, "SO");
//         else
//             free_cube(cube, "Texture daha önce tanımlanmış");

//     }
// 	else if (!ft_strncmp((line + i), "NO ", 3))
//     {
//         if (cube->text.no == NULL)
//             cube->text.no = texture_path(cube, line + i, "NO");
//         else
//             free_cube(cube, "Texture daha önce tanımlanmış");
//     }
// 	else if (!ft_strncmp((line + i), "WE ", 3))
//     {
//         if (cube->text.we == NULL)
//             cube->text.we = texture_path(cube, line, "WE");
//         else
//             free_cube(cube, "Texture daha önce tanımlanmış");
//     }
// 	else if (!ft_strncmp((line + i), "EA ", 3))
//     {
//         if (cube->text.ea == NULL)
//             cube->text.ea = texture_path(cube, line, "EA");
//         else
//             free_cube(cube, "Texture daha önce tanımlanmış");
//     }
// 	return 0;
// }

int zero_check(t_cube *cube)
{
    if(!cube->text.no || !cube->text.so || !cube->text.we ||!cube->text.ea 
        ||(cube->text.f_check != 1 )||(cube->text.c_check != 1))
        return(1);
    return 0;
}