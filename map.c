#include "cub3d.h"

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

void find_map_start(t_cube *cube)
{
    int i;

    i = 0;
    while (cube->lines[i])
    {
        if (is_map_line(cube->lines[i]))
        {
            cube->map.map_start = i;
            return;
        }
        i++;
    }
    if (cube->map.map_start == 0)
        free_cube(cube, "There is no map");
}

int	map_alloc(t_cube *cube)
{
	int	i;
    int j;
    int k;

    j = cube->map.map_start;
	cube->map.maps = ft_calloc(sizeof(char *) * (cube->map.height + 1),1);
    cube->map.n_maps = ft_calloc(sizeof(char *) * (cube->map.height + 1),1);
	if (!cube->map.maps || !cube->map.n_maps)
		return (1);
	i = 0;
	while (i < cube->map.height)
	{
        k = ft_strlen(cube->lines[j]);
		cube->map.maps[i] = ft_calloc(k + 1, 1);
        cube->map.n_maps[i] = ft_calloc(k + 1, 1);
		if (!cube->map.maps[i] || !cube->map.n_maps[i])
			return (1);
		i++;
        j++;
	}
	cube->map.maps[i] = NULL;
    cube->map.n_maps[i] = NULL;
	return (0);
}
void	fill_map_n(t_cube *cube, int i)
{
	int	j;
	int	k;
    int l;

	j = 0;
	k = cube->map.map_start + i;
    l = ft_strlen(cube->lines[k]);
	while (j < l)
	{
		if (cube->lines[k][j])
			cube->map.n_maps[i][j] = cube->lines[k][j];
		j++;
	}
	cube->map.n_maps[i][j] = '\0';
}

void	fill_map(t_cube *cube, int i)
{
	int	j;
	int	k;
    int l;

	j = 0;
	k = cube->map.map_start + i;
    l = ft_strlen(cube->lines[k]);
	while (j < l)
	{
		if (cube->lines[k][j]
			&& cube->lines[k][j] != '\n')
			cube->map.maps[i][j] = cube->lines[k][j];
		j++;
	}
	cube->map.maps[i][j] = '\0';
}