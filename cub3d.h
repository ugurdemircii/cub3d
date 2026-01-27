#ifndef CUB3D.H 
# define CUB3D.H 

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_player
{
    int     x;     
    int     y; 
    char    dir;
} t_player;

typedef struct s_text
{
    char *ea;
    char *we;
    char *no;
    char *so;
    int fd;
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

#endif