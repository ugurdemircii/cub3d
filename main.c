#include "cub3d.h"


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


static int	get_map(t_cube *cube)
{
    int	i;
    find_map_start(cube);
    count_map_height(cube);
    count_map_width(cube);
	if (map_alloc(cube))
    return (1);
	i = -1;
	while (++i < cube->map.height)
        fill_map(cube, i);
    i = -1;
    while (++i < cube->map.height)
    {
        fill_map_n(cube, i);
    }
	return (0);
}


int map_check(t_cube *cube)
{
    if (check_map_after(cube))
        free_cube(cube, "Character after map");
    if (up_down_check(cube))
        free_cube(cube, "Open border");
    if (check_sides(cube))
        free_cube(cube, "Open map from sides");
    if (!locate_player(cube))
        free_cube(cube, "wrong amount of player");
    if (handle_space_player(cube))
        free_cube(cube, "Space next to player");
    handle_space(cube);
    int j;

    j= -1;
    while(cube->map.maps[++j])
        printf("%s\n",cube->map.maps[j]);
    return 0;
}






int parser(t_cube *cube, char **argv)
{
    int i;

    init_textures(cube);
    if (check_path(cube,argv[1]))
        free_cube(cube, "Dosyayla ilgili hata");
    read_lines(cube, argv[1]);
    i = 0;
    while (cube->lines[i])
    {
        if (is_maps_line(cube->lines[i]))
            break;
        if (cube->lines[i][0] == '\0')
        {
            i++;
            continue;
        }
        texture_check(cube, cube->lines[i]);
        parse_colour(cube, cube->lines[i]);    
        i++;
    }
    if (zero_check(cube))
        free_cube(cube, "Wrong amount of texture or colour");
    get_map(cube);
    map_check(cube);
    return 0;
}


int main(int argc, char **argv)
{
    t_cube cube;

    if (argc != 2)
    {
        printf("Error\n Invalid argc\n");
        return 1;
    }
    if (parser(&cube, argv))
        return 1;
     printf("%d %d",cube.player.x,cube.player.y);
    //  exit(1);
    render(&cube);
    return 0;
}