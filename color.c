#include "cub3d.h"

int colour_analysis(char **colour)
{   
    long long value;
    int j;
    int k;

    j = -1;
    while (colour[++j])
    {
        k = -1;
        while(colour[j][++k])
        {
            if ((!ft_isdigit(colour[j][k])) && (!ft_isspace(colour[j][k])))
                return (1);
        }
    }
    j = -1;
    while (++j < 3)
    {
        if (colour[j][0] == '\n')
            return 1;
        value = ft_atoi(colour[j]);
        if (value < 0 || value > 255)
            return 1;
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

void assign_colour_values(t_cube *cube, char type)
{
    int k;

    k = 0;
    if (!cube->text.colour[0] || !cube->text.colour[1] || !cube->text.colour[2])
        free_cube(cube, "Missing colour part");
    while (ft_isspace(cube->text.colour[2][k]))
        k++;
    if (cube->text.colour[2][k] == '\0')
        free_cube(cube, "invalid space");
    if (colour_analysis(cube->text.colour))
        free_cube(cube, "Invalid rgb value");
    if (type == 'F')
    {
        cube->text.f_check++;
        cube->text.floor = add_colour(cube->text.colour);
    }
    else if (type == 'C')
    {
        cube->text.c_check++;
        cube->text.ceiling = add_colour(cube->text.colour);
    }
    free_colour(cube);
}

void process_colour_string(t_cube *cube, char *str, char type)
{
    char    *trimmed;
    int     count;
    int     j;

    count = 0;
    j = -1;
    trimmed = ft_strtrim(str, " ");
    while (trimmed[++j])
    {
        if (trimmed[j] == ',')
            count++;
    }
    cube->text.colour = ft_split(trimmed, ',');
    free(trimmed);
    if (count != 2 || !cube->text.colour)
        free_cube(cube, "Wrong amount of colour part");
    assign_colour_values(cube, type);
}

int parse_colour(t_cube *cube, char *line)
{
    int i;

    i = 0;
    cube->text.colour = NULL;
    while (ft_isspace(line[i]))
        i++;
    if ((line[i] == 'F' || line[i] == 'C') && ft_isspace(line[i + 1]))
        process_colour_string(cube, line + i + 1, line[i]);
    return (0);
}

// int parse_colour(t_cube *cube, char *line)
// {
//     char    *trimmed;
//     int i;
//     int count;
//     int j ;
//     int k;
    
//     count = 0;
//     k = 0;
//     j = -1;
//     i = -1;
//     cube->text.colour = NULL;
//     while (ft_isspace(line[++i]))
//         ;
//     if ((line[i] == 'F' || line[i] == 'C') && ft_isspace(line[i + 1]))
//     {

//         trimmed = ft_strtrim(line + 1 + i, " ");
//         while(trimmed[++j])
//         {
//             if(trimmed[j] == ',')
//                 count++;
//         }
//         cube->text.colour = ft_split(trimmed, ',');
//         free(trimmed);
//         if (count != 2)
//             free_cube(cube, "Wrong amount of colour part");
//         if (!cube->text.colour || !cube->text.colour[0] || !cube->text.colour[1] || !cube->text.colour[2])
//             free_cube(cube, "Missing colour part");
//         while (ft_isspace(cube->text.colour[2][k]))
//             k++;
//         if (cube->text.colour[2][k] == '\0')
//             free_cube(cube, "invalid space");
//         if (colour_analysis(cube->text.colour))
//             free_cube(cube, "Invalid rgb value");
//         if (line[i] == 'F')
//         {
//             cube->text.f_check++;
//             cube->text.floor = add_colour(cube->text.colour);
//         }
//         if (line[i] == 'C')
//         {
//             cube->text.c_check++;
//             cube->text.ceiling = add_colour(cube->text.colour);
//         }
//         free_colour(cube);
//     }
//     return 0;
// }
