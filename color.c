#include "cub3d.h"

int colour_analysis(char **colour)
{   
    int value;
    int i;

    i = 0;
    while (i < 3)
    {
        value = atoi(colour[i]);
        if (value < 0 || value > 255)
            return 1;
        i++;
    }
    return 0;
}


static unsigned long add_colour(char **colour)
{
	unsigned long	result;
	int				r;
	int				g;
	int				b;

	r = atoi(colour[0]);
	g = atoi(colour[1]);
	b = atoi(colour[2]);
	result = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return (result);
}

int parse_colour(t_cube *cube, char *line)
{
    char    **colour;
    char    *trimmed;
    int     r;
    int     g;
    int     b;

    
    if (line[0] == 'F' || line[0] == 'C')
    {
        trimmed = ft_strtrim(line + 1, " ");
        colour = ft_split(trimmed, ',');
        free(trimmed);
        
        if (!colour || !colour[0] || !colour[1] || !colour[2] || colour[3])
            return 1;
        if (colour_analysis(colour))
        {
            printf("wrong colour");
            fflush(stdout);
            return 1;
        }
        if (line[0] == 'F')
            cube->text.floor = add_colour(colour);
        if (line[0] == 'C')
            cube->text.ceiling = add_colour(colour);
    }

    return 0;
}