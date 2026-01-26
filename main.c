#include "cub3d.h"

int ft_strlen(char *set)
{
    int i;

    i = 0;
    while(set[i])
        i++;
    return i;
}

char *texture_path(t_cube *cube,char *path,char *set)
{
    char    *texts;
    char    *line;
    int     len;
    int     fd;

    texts = ft_strtrim(path, set);
    if (!texts)
        return (NULL);

    line = ft_strtrim(texts, " ");
    free(texts);
    if (!line)
        return (NULL);
    
    len = ft_strlen(line);
    if (len < 4)
    {
        free(line);
        return (NULL);
    }
    if ((line[len - 4] != '.' || line[len - 3] != 'x'
        || line[len - 2] != 'p' || line[len - 1] != 'm'))
            return (NULL);
    return(line);

}

void texture_check(t_cube *cube,char *line)
{
 
	if (!ft_strncmp(line, "SO ", 3))
    {
        if (cube->text.so)
        {
            printf("daha önce tanımlanmış");
            return;
        }
		cube->text.so = texture_path(cube, line, "SO");
    }
	else if (!ft_strncmp(line, "NO ", 3))
    {
		if (cube->text.no)
        {
            printf("daha önce tanımlanmış");
            return;
        }
		cube->text.no = texture_path(cube, line, "NO");
    }
	else if (!ft_strncmp(line, "WE ", 3))
    {
        if (cube->text.we)
        {
            printf("daha önce tanımlanmış");
            return;
        }
		cube->text.we = texture_path(cube, line, "WE");
    }
	else if (!ft_strncmp(line, "EA ", 3))
    {
        if (cube->text.ea)
        {
            printf("daha önce tanımlanmış");
            return;
        }
        cube->text.ea = texture_path(cube, line, "EA");
    }
	else
		return NULL;

}

// int	is_valid(char c)
// {
// 	if (c == '1' || c == '0' || c == ' '
// 		|| c == 'N' || c == 'S' || c == 'E' || c == 'W')
//         return 1;
//     return 0;
// }

// int is_empty_line(char *line)
// {
//     int i = 0;
    
//     if (!line)
//         return (1);
    
//     while (line[i])
//     {
//         if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n'
//             && line[i] != '\r' && line[i] != '\v')
//             return (0);
//         i++;
//     }
//     return (1);
// }

// int up_down_check(t_cube *cube,t_map *map)
// {
//     int i;

//     i = 0; 
//     while(map->maps[0][i])
//     {
//         if (map->maps[0][i++] != 0)
//             return 0;
//     }
//     i = 0;
//     while(map->maps[map->height][i])
//     {
//         if (map->maps[map->height][i++] != 0)
//             return 0;
//     }
// }


int check_path(t_cube *cube, char *path)
{
    char	*line;
    int		count;
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
        
        
        // count = 0;
        // while (line)
        // {
            // 	line = get_next_line(cube->fd);
            // 	if (!line)
            // 		break ;
            // 	free(line);
            // 	count++;
            // }
            
            // return (0);
    return 0;
}
int read_lines(t_cube *cube, char *path)
{
    int fd;
    int i;
    char *line;

    fd = open(path,O_RDONLY);
    i = 0;

    line = get_next_line(fd);
    while(line)
    {
        free(line);
        i++;
        line = get_next_line(fd);
    }

    free(line);
    close(fd);

    if (!i)
    {
        printf("dosya boş");
        return (1);
    }

    cube->lines = malloc(sizeof(char *)* (i + 1));

    if (!cube->lines)
        return 1;


    fd = open(path,O_RDONLY);
    i = 0;
    while((line = get_next_line(fd))!=NULL)
    {
        cube->lines[i] = line;
        i++;
    }

    cube->lines[i] = NULL;

    printf("8");
    return (0);



}

static int	locate_player(t_cube *cube)
{
	int	i;
    int	j;
	int	player;
	
    i = 0;
    player = 0;
	while (i < cube->map.height)
	{
		j = 0;
		while (j < cube->map.width)
		{
			
			if (cube->map.maps[i][j] == 'N' || cube->map.maps[i][j] == 'S' || 
				cube->map.maps[i][j] == 'E' || cube->map.maps[i][j] == 'W')
			{
				++player;
				cube->player.x = i;
				cube->player.y = j;
				cube->player.dir = cube->map.maps[i][j];
			}
			j++;
		}
		i++;
	}
    if(player != 1)
    {
        printf("wrong amount of player");
        return 0;
    }
	return (player);
}


int parser(t_cube *cube, char **argv)
{
    if (check_path(cube,argv[1]))
    {
        printf("dosyayla ilgili hata");
        return(1);
    }
    if (read_lines(cube, argv[1]))
    {
        printf("dosya okumayla ilgili hata");
        return 1;
    }

    texture_check(cube,);//color kısmı hiç yok

    make_map;
        
        
    return 0;
}

int main(int argc, char **argv)
{
    t_cube cube;

    if (argc != 2)
        return 1;
    
    if (parser(&cube, argv))
        //error
        return 1;
    return 0;
}