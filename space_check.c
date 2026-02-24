#include "cub3d.h"

int handle_space_player(t_cube *cube)
{
    int x;
    int y;

    x = cube->player.x;
    y = cube->player.y;
    if (x > 0 && (cube->map.n_maps[x - 1][y] == ' ' || cube->map.n_maps[x - 1][y] == '\n'))
        return (1);

    if (x < cube->map.height - 1 && (cube->map.n_maps[x + 1][y] == ' ' || cube->map.n_maps[x + 1][y] == '\n' ))
        return (1);

    if (y > 0 && (cube->map.n_maps[x][y - 1] == ' ' || cube->map.n_maps[x][y - 1] == '\n' ))
        return (1);

    if (y < cube->map.width - 1 && (cube->map.n_maps[x][y + 1] == ' ' || cube->map.n_maps[x][y + 1] == '\n' ))
        return (1);

    return (0); 
}

// static int is_invalid(t_cube *cube, int i, int j)
// {
//     // int w;

//     // w = ft_strlen(cube->map.maps[i]) - 1;
//     if (i > 0 && cube->map.maps[i-1][j] == '0')
//     {
//         printf("Hata!!\n");
//         printf("%d %d\n",i,j );
//         printf("%d\n",cube->map.maps[i-1][32]);
//         return 1;
//     }
//     if (i < cube->map.height - 1 && cube->map.maps[i+1][j] == '0')
//         return 1;
//     if (j > 0 && cube->map.maps[i][j-1] == '0')
//         return 1;
//     if (j < cube->map.width - 1 && cube->map.maps[i][j+1] == '0')
//         return 1;
//     return 0;
// }
static int is_invalid(t_cube *cube, int i, int j)
{
    char **map = cube->map.maps;
    int height = cube->map.height;

    if (i - 1 >= 0)
    {
        if (j >= ft_strlen(map[i - 1]) || map[i - 1][j] == '0')
            return (1);
    }
    if (i + 1 < height)
    {
        if (j >= ft_strlen(map[i + 1]) || map[i + 1][j] == '0')
            return (1);
    }
    if (j - 1 >= 0 && map[i][j - 1] == '0')
        return (1);

    if (j + 1 < ft_strlen(map[i]) && map[i][j + 1] == '0')
        return (1);

    return (0);
}

static int is_invalid_zero(char **map, int height, int i, int j)
{
    if (i - 1 < 0 || map[i - 1][j] == '\0' || map[i - 1][j] == ' ')
        return (1);
    if (i + 1 >= height || map[i + 1][j] == '\0' || map[i + 1][j] == ' ')
        return (1);
    if (j - 1 < 0 || map[i][j - 1] == '\0' || map[i][j - 1] == ' ')
        return (1);
    if (map[i][j + 1] == '\0' || map[i][j + 1] == ' ')
        return (1);
    return (0);
}

static void process_space(t_cube *cube, int i, int j)
{
    // if (cube->map.maps[i][j] == ' ')
    // {
    //     if (is_invalid(cube, i, j))
    //         free_cube(cube, "Wrong space place");
    // }
    if (cube->map.maps[i][j] == '0')
    {
        if (is_invalid_zero(cube->map.maps,cube->map.height, i, j))
            free_cube(cube, "Wrong 0 place" );
    }
}

void handle_space(t_cube *cube)
{
    int i;
    int j;
    int k;

    i = 0;
    while (i < cube->map.height)
    {
        k = ft_strlen(cube->map.maps[i]);
        j = 0;
        while (j < k)
        {
            process_space(cube, i, j);
            j++;
        }
        i++;
    }
}