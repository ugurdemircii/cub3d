#include "cub3d.h"

static int space_check(t_cube *cube, int i, int j)
{
    int w;

    w = ft_strlen(cube->map.maps[i]) - 1;
    if (i == 0 || i == cube->map.height - 1)
    {
        if (cube->map.maps[i][j] != '1' && cube->map.maps[i][j] != ' ')
            return (1); 
    }

    if (j == 0 || j == w)
    {
        if (cube->map.maps[i][j] != '1' && cube->map.maps[i][j] != ' ')
            return (1);
    }

    return (0);
}

int check_map_after(t_cube *cube)
{
    int i;
    int j;

    i = cube->map.map_start + cube->map.height;
    while(cube->lines[i])
    {
        j = 0;
        while(cube->lines[i][j])
        {
            if (cube->lines[i][j] != ' ' && cube->lines[i][j] != '\t'
				&& cube->lines[i][j] != '\r' && cube->lines[i][j] != '\n'
				&& cube->lines[i][j] != '\v' && cube->lines[i][j] != '\f')
                return (1);
            j++;
        }
        i++;
    }
    return(0);
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
	while (cube->map.maps[cube->map.height - 1][i])
	{
		if (cube->map.maps[(cube->map.height) - 1][i] != '1' &&
			cube->map.maps[(cube->map.height) - 1][i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	check_sides(t_cube *cube)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(cube->map.maps[0]);
	while (i < len)
	{
		if (space_check(cube, 0, i))
			return (1);
		i++;
	}
	i = 0;
	len = ft_strlen(cube->map.maps[cube->map.height - 1]);
	while (i < len)
	{
		if (space_check(cube,
				cube->map.height - 1, i))
			return (1);
		i++;
	}
	i = 1;
	while (i < cube->map.height - 1)
	{
		len = ft_strlen(cube->map.maps[i]);
		if (space_check(cube, i, 0))
			return (1);
		if (space_check(cube, i, len - 1))
			return (1);
		i++;
	}
	return (0);
}

int	locate_player(t_cube *cube)
{
	int	i;
    int	j;
	int	player;
	
    i = -1;
    player = 0;
	while (++i < cube->map.height)
	{
		j = -1;
		while (++j < (int)ft_strlen(cube->map.maps[i]))
		{
			
			if (cube->map.maps[i][j] == 'N' || cube->map.maps[i][j] == 'S' || 
				cube->map.maps[i][j] == 'E' || cube->map.maps[i][j] == 'W')
			{
				++player;
				cube->player.x = i;
				cube->player.y = j;
				cube->player.dir = cube->map.maps[i][j];
			}
		}
	}
    if (player != 1)
        return 0;
    return (player);
}
