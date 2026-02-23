#include "cub3d.h"

void init_textures(t_cube *cube)
{
    cube->text.no = NULL;
    cube->text.so = NULL;
    cube->text.we = NULL;
    cube->text.ea = NULL;
    cube->text.floor = -1;
    cube->text.ceiling = -1;
    cube->text.f_check = 0;
    cube->text.c_check = 0;
    cube->map.map_start=0;
    cube->map.height=0;
    cube->map.width=0;
    cube->player.x = 0;
	cube->player.y = 0;
    cube->lines = NULL;
    cube->map.maps = NULL;
    cube->map.n_maps = NULL;
    cube->text.colour = NULL;
}

static void free_textures(t_cube *cube)
{
    if (cube->text.no)
        free(cube->text.no);
    if(cube->text.we)
        free(cube->text.we);
    if (cube->text.so)
	    free(cube->text.so);
	if (cube->text.ea)
	    free(cube->text.ea);
    return ;
}


void	free_cube(t_cube *cube, char *msg)
{
    printf("Error\n");
    printf("%s\n",msg);
    int	i;

	if (cube->lines)
	{
        i = -1;
		while (cube->lines[++i])
            free(cube->lines[i]);
		free(cube->lines);
	}
	if (cube->map.maps)
	{
        i = -1;
		if (cube->map.maps[++i])
        {
            while(cube->map.maps[i])
                free(cube->map.maps[i++]);
        }
        free(cube->map.maps);
    }
    if (cube->map.n_maps)
	{
        i = -1;
		if (cube->map.n_maps[++i])
        {
            while(cube->map.n_maps[i])
                free(cube->map.n_maps[i++]);
        }
        free(cube->map.n_maps);
    }
    free_textures(cube);
    exit(1);
}
