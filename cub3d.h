#ifndef CUB3D_H 
# define CUB3D_H 

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "get_next_line.h"

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
    char    **n_maps;
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
int     ft_isspace(int c);
void	free_cube(t_cube *cube, char *msg);
int     check_map_after(t_cube *cube);
int     up_down_check(t_cube *cube);
int	check_sides(t_cube *cube);
int	locate_player(t_cube *cube);
int texture_check(t_cube *cube,char *line);
int check_path(t_cube *cube, char *path);
void read_lines(t_cube *cube, char *path);
int	is_valid(char c);
int	is_char(char c);
int	is_maps_line(char *line);
int is_map_line(char *line);
void    count_map_height(t_cube *cube);
void	count_map_width(t_cube *cube);
void	fill_map_n(t_cube *cube, int i);
void	fill_map(t_cube *cube, int i);
int	map_alloc(t_cube *cube);
int handle_space_player(t_cube *cube);
void handle_space(t_cube *cube);
int zero_check(t_cube *cube);
void init_textures(t_cube *cube);
void find_map_start(t_cube *cube);
#endif