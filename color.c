#include "cub3d.h"

int colour_analysis(char **colour)
{   
    int value;
    int i;
    int j;
    int k;

    j = -1;
    i = 0;
    while (colour[++j])
    {
        k = -1;
        while(colour[j][++k])
        {
            if ((!ft_isdigit(colour[j][k])) &&( !ft_isspace(colour[j][k])))
            {
                //printf("atoiden önce hata\n");
                exit(1);
            }
        }
    }
    while (i < 3)
    {
        value = ft_atoi(colour[i]);
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

	r = ft_atoi(colour[0]);
	g = ft_atoi(colour[1]);
	b = ft_atoi(colour[2]);
	result = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return (result);
}
int	ft_isspace(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

void free_colour(t_cube *cube)
{
    int	i;
    
    if (cube->text.colour)
	{
        i = -1;
		while (cube->text.colour[++i])
            free(cube->text.colour[i]);
		free(cube->text.colour);
	}
}

int parse_colour(t_cube *cube, char *line)
{
    char    *trimmed;
    int i;

    i = -1;

    while (ft_isspace(line[++i]))
        ;
    // printf("%d--\n",i);
    if ((line[i] == 'F' || line[i] == 'C') && ft_isspace(line[i + 1]))
    {
        trimmed = ft_strtrim(line + 1 + i, " ");
        cube->text.colour = ft_split(trimmed, ',');
        free(trimmed);
        
        // printf("colour%s--\n",colour[2]);
        if (!cube->text.colour || !cube->text.colour[0] || !cube->text.colour[1] || !cube->text.colour[2] || cube->text.colour[3])
        {
            printf("eksik renk\n");
            exit(1);
        }
        if (colour_analysis(cube->text.colour))
        {
            printf("wrong colour");
            fflush(stdout);
            return 1;
        }
        if (line[i] == 'F')
        {
            cube->text.f_check++;
            cube->text.floor = add_colour(cube->text.colour);
            //printf("%d--\n",cube->text.floor);
        }
        if (line[i] == 'C')
        {
            cube->text.c_check++;
            cube->text.ceiling = add_colour(cube->text.colour);
        }
        if (cube->text.colour)
        {
            free_colour(cube);
        }
    }
    return 0;
}