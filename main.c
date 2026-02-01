#include "cub3d.h"


char *texture_path(t_cube *cube, char *path, char *set)
{
    char *trim;
    char *line;
    int   len;

    // remove "NO ", "SO ", etc
    trim = ft_strtrim(path, set);
    if (!trim)
        return NULL;

    line = ft_strtrim(trim, " ");
    free(trim);
    if (!line)
        return NULL;

    // remove trailing newline
    len = ft_strlen(line);
    if (len > 0 && line[len - 1] == '\n')
    {
        line[len - 1] = '\0';
        len--;
    }

    // check extension
    if (len < 4 ||
        line[len - 4] != '.' ||
        line[len - 3] != 'x' ||
        line[len - 2] != 'p' ||
        line[len - 1] != 'm')
    {
        printf("Invalid texture: [%s]\n", line);
        free(line);
        return NULL;
    }

    return line;
}


int texture_check(t_cube *cube,char *line)
{
    char *l;

    if (!line)
        return (1);

    // Skip leading whitespace
    l = line;
    while (*l == ' ' || *l == '\t')
        l++;

    // Skip empty lines
    if (*l == '\0' || *l == '\n')
        return (0);
	if (!ft_strncmp(line, "SO ", 3))
    {
        if (cube->text.so == NULL)
            cube->text.so = texture_path(cube, line, "SO");
        else
        {
            printf("daha önce tanımlanmış");
            return 1;
        }
    }
	else if (!ft_strncmp(line, "NO ", 3))
    {

        if (cube->text.no == NULL)
            cube->text.no = texture_path(cube, line, "NO");
        else
        {
            printf("daha önce tanımlanmış");
            return 1;
        }
    }
	else if (!ft_strncmp(line, "WE ", 3))
    {
        if (cube->text.we == NULL)
            cube->text.we = texture_path(cube, line, "WE");
        else
        {
            printf("daha önce tanımlanmış");
            return 1;
        }
    }
	else if (!ft_strncmp(line, "EA ", 3))
    {
        if (cube->text.ea == NULL)
            cube->text.ea = texture_path(cube, line, "EA");
        else
        {
            printf("daha önce tanımlanmış");
            return 1;
        }
    }
    
	return 0;
    
}

int	is_valid(char c)
{
	if (c == '1' || c == '0' || c == ' '
		|| c == 'N' || c == 'S' || c == 'E' || c == 'W')
        return 1;
    return 0;
}

int	is_char(char c)
{
	if (c == '0' ||c == 'N' || c == 'S' ||
        c == 'E' || c == 'W')
        return 1;
    return 0;
}


static int	is_maps_line(char *line)
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
		else if (line[i] != '0' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E'
			&& line[i] != 'W' && line[i] != ' ')
			return (0);
		i++;
	}
	return (w);
}

void    count_map_height(t_cube *cube)
{
	int	i;
	int	height;

	height = 0;
	i = cube->map.map_start;
	while (cube->lines[i])
	{
		if (is_maps_line(cube->lines[i]))
			height++;
		else
			break ;
		i++;
	}

	cube->map.height = height;
}

void	count_map_width(t_cube *cube)
{
	int	i;
	int	j;
	int	max;
    int h;

	max = 0; 
    h = cube->map.map_start + cube->map.height;
	i = cube->map.map_start;
	while (i < h)
	{
		j = 0;
		while (cube->lines[i][j] && cube->lines[i][j] != '\n')
			j++;
		if (j > max)
			max = j;
		i++;
	}
	cube->map.width = max;
}

int is_empty_line(char *line)
{
    int i = 0;
    
    if (!line)
        return (1);
    
    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n'
            && line[i] != '\r' && line[i] != '\v')
            return (0);
        i++;
    }
    return (1);
}

int up_down_check(t_cube *cube)
{
    int i;

    i = 0; 
    while (cube->map.maps[0][i])
	{
		if (cube->map.maps[0][i] != '1' && cube->map.maps[0][i] != ' ')
			return (1);
		i++;
	}
	i = 0;
    printf("-*-*%s-*-*-",cube->map.maps[cube->map.height - 1]);
	while (cube->map.maps[cube->map.height - 1][i])
	{
		if (cube->map.maps[cube->map.height - 1][i] != '1' &&
			cube->map.maps[cube->map.height - 1][i] != ' ')
			return (1);
		i++;
	}
	return (0);
}


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

int is_valid_map_char(char c)
{
    return (c == '1' || c == '0' || c == 'N' ||
            c == 'S' || c == 'E' || c == 'W' || c == ' ' || c == '\n');
}

int is_map_line(char *line)
{
    int i = 0;
    int has_wall = 0;

    // skip leading spaces
    while (line[i] == ' ')
        i++;

    while (line[i])
    {
        if (!is_valid_map_char(line[i]))
        {
            printf("AĞĞĞĞĞĞ");
            return 0;
        }
        if (line[i] == '1')
            has_wall = 1;
        i++;
    }
    printf("%s  duvar: %d\n",line,has_wall);
    return has_wall;
}

void find_map_start(t_cube *cube)
{
    int i = 0;

    while (cube->lines[i])
    {
        printf("%s\n",cube->lines[i]);
        if (is_map_line(cube->lines[i]))
        {
            cube->map.map_start = i;
            return;
        }
        i++;
    }
    printf("no map\n");
    free_cube(cube);
}

// void find_map_start(t_cube *cube)
// {
//     int i = 0;
//     int j;

//     while (cube->lines[i])
//     {
//         j = 0;
//         int wall = 0;

//         while (cube->lines[i][j] && cube->lines[i][j] != '\n')
//         {
//             if (!is_valid_map_char(cube->lines[i][j]))
//                 break;
            
//             if (cube->lines[i][j] == '1')
//                 wall = 1;
//             j++;
//         }
//         if (wall && cube->lines[i][j] == '\0')
//         {
//             printf("%s",cube->lines[i]);
//             cube->map.map_start = i;
//             return;
//         }
//         i++;
//     }

//     printf("no map\n");
//     free_cube(cube);
// }


static int	space_check(t_cube *cube, int i, int j)
{
	if (i == 0 || i == cube->map.height - 1)
		return (1);
	if (j == 0 || j == cube->map.width - 1)
		return (1);
	if (cube->map.maps[i - 1][j] == ' ' ||cube->map.maps[i + 1][j] == ' '
        || cube->map.maps[i][j - 1] == ' ' || cube->map.maps[i][j + 1] == ' ')
		return (1);
	return (0);
}

static int	check_sides(t_cube *cube)
{
	int	i;
	int	j;

	i = 0;
	while (i < cube->map.height)
	{
		j = 0;
		while (j < cube->map.width)
		{
			if (is_char(cube->map.maps[i][j])
				&& space_check(cube, i, j))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	map_alloc(t_cube *cube)
{
	int	i;

	cube->map.maps = malloc(sizeof(char *) * (cube->map.height + 1));
	if (!cube->map.maps)
		return (1);
	i = 0;
	while (i < cube->map.height)
	{
		cube->map.maps[i] = malloc(cube->map.width + 1);
		if (!cube->map.maps[i])
			return (1);
		i++;
	}
	cube->map.maps[i] = NULL;
	return (0);
}

// static void fill_map(t_cube *cube, int i)
// {
//     int j = 0;
//     int k = cube->map.map_start + i;
//     int len = ft_strlen(cube->lines[k]);

//     // Remove trailing newline
//     if (len > 0 && cube->lines[k][len - 1] == '\n')
//         len--;

//     while (j < cube->map.width)
//     {
//         if (j < len)
//             cube->map.maps[i][j] = cube->lines[k][j];
//         else
//             cube->map.maps[i][j] = ' ';
//         j++;
//     }
//     cube->map.maps[i][j] = '\0';
// }

static void	fill_map(t_cube *cube, int i)
{
	int	j;
	int	k;

	j = 0;
	k = cube->map.map_start + i;
	while (j < cube->map.width)
	{
		if (cube->lines[k][j]
			&& cube->lines[k][j] != '\n')
			cube->map.maps[i][j] = cube->lines[k][j];
		else
			cube->map.maps[i][j] = ' ';
		j++;
	}
	cube->map.maps[i][j] = '\0';
}

static int	get_map(t_cube *cube)
{

	int	i;
    find_map_start(cube);
    printf("start:%d\n",cube->map.map_start);
    fflush(stdout);
    count_map_height(cube);
    printf("heigth:%d\n",cube->map.height);
    fflush(stdout);
    count_map_width(cube);
    printf("width:%d\n",cube->map.width);
    fflush(stdout);
	if (map_alloc(cube))
		return (1);

    
	i = -1;
	while (++i < cube->map.height)
        fill_map(cube, i);
    int j= -1;
    while(cube->map.maps[++j])
        printf("%s\n",cube->map.maps[j]);

    //printf("%d---",cube->map.height);
	return (0);
}


static void handle_space(t_cube *cube)
{
    int i;
    int j;

    i = 0;
    while (i < cube->map.height)
    {
        j = 0;
        while(j < cube->map.width)
        {
            if (cube->map.maps[i][j] == ' ')
            {
                if (cube->map.maps[i+1][j] == '0' || cube->map.maps[i-1][j] == '0'
                || cube->map.maps[i][j+1] == '0' || cube->map.maps[i][j-1] == '0')
                {
                    printf("wrong space place");
                    free_cube(cube);
                }
                else
                {
                    cube->map.maps[i][j] = '1';
                }
            }
            j++;
        }
        i++;
    }
    
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
    if (player != 1)
        return 0;
	return (player);
}

int map_check(t_cube *cube)
{
    
    if (up_down_check(cube) || check_sides(cube))
    {
        printf("harita geçerlilikle ilgili hata");
        free_cube(cube);
    }
    if(!locate_player(cube))
    {
        printf("wrong amount of player");
        free_cube(cube);
    }
    return 0;
}

void init_textures(t_cube *cube)
{
    cube->text.no = NULL;
    cube->text.so = NULL;
    cube->text.we = NULL;
    cube->text.ea = NULL;
    cube->text.floor = 0;
    cube->text.ceiling = 0;
    cube->map.map_start=0;
    cube->map.height=0;
    cube->map.width=0;
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
        free_cube(cube);
    }
    //int i = -1;
    // while(cube->lines[++i])
    // {
    //     printf("%s",cube->lines[i]);
    //     fflush(stdout);

    // }
    init_textures(cube);
    int i = 0;

    while (cube->lines[i])
    {
       // printf("LINE[%d]: [%s]\n", i, cube->lines[i]);

        if (is_maps_line(cube->lines[i]))
            break;
        if (cube->lines[i][0] == '\0')
        {
            i++;
            continue;
        }
        if (texture_check(cube, cube->lines[i]))
        {
            printf("Texture hatası %d: %s\n", i + 1, cube->lines[i]);
            fflush(stdout);
            free_cube(cube);
            //return (1);
        }
        if (parse_colour(cube, cube->lines[i]))
        {
            printf("renk hatası %d: %s\n", i + 1, cube->lines[i]);
            fflush(stdout);
            free_cube(cube);
            //return (1);
        }

        i++;
    }
    
    get_map(cube);

    if (map_check(cube))
    {
        printf("haritayla ilgili hata");
        return 1;
    }
        
        
    return 0;
}

void	free_textures(t_cube *cube)
{
	if (cube->text.no)
		free(cube->text.no);
	if (cube->text.so)
		free(cube->text.so);
	if (cube->text.we)
		free(cube->text.we);
	if (cube->text.ea)
		free(cube->text.ea);
}


void	free_cube(t_cube *cube)
{
	int	i;

	if (cube->lines)
	{
		i = 0;
		while (cube->lines[i])
			free(cube->lines[i++]);
		free(cube->lines);
	}
	if (cube->map.maps)
	{
		i = 0;
		while (cube->map.maps[i])
			free(cube->map.maps[i++]);
		free(cube->map.maps);
	}
    free_textures(cube);
    exit(1);
}


int main(int argc, char **argv)
{
    t_cube cube;

    if (argc != 2)
        return 1;
    printf("b");
    fflush(stdout);
    if (parser(&cube, argv))
        //error
        return 1;
    return 0;
}