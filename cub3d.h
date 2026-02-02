#ifndef CUB3D_H 
# define CUB3D_H 

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"

typedef struct s_player
{
    int     x;     
    int     y; 
    char    dir;
} t_player;

typedef struct s_text
{
    char **colour;
    char *ea;
    char *we;
    char *no;
    char *so;
    int fd;
    int floor;
    int ceiling;
    int f_check;
    int c_check;
} t_text;

typedef struct s_map
{
    char    **maps;
    int     width;
    int     height;
    int     map_start;

} t_map;

typedef struct s_cube
{
    t_map map;
    int  fd;
    int  mapline;
    t_text text;
    char **lines;
    t_player player;

} t_cube;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*ft_strtrim(char const *s1, char const *set);
int     parse_colour(t_cube *cube, char *line);
void	free_cube(t_cube *cube);
int	ft_isspace(int c);

#endif