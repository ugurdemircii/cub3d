#ifndef CUB3D_H 
# define CUB3D_H 

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
# include <math.h>
# include "mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>

// #include "a.h"

typedef struct s_values
{
    double cam_x;
    double plane_x; 
    double plane_y;
    double dir_x; 
    double dir_y;
    double raydir_x; 
    double raydir_y;
    double delta_x;
    double delta_y;
    double spos_x;
    double spos_y;
    double perp_x;
    double perp_y;
    int map_x;
    int map_y;
    int step_x;
    int step_y;
}t_values;

typedef struct s_game
{
    int posx;
    int posy;
    double angle;
    void *mlx;
    void *win;
    char **map;
}t_game;


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
    t_game *game;
} t_cube;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*ft_strtrim(char const *s1, char const *set);
int     parse_colour(t_cube *cube, char *line);
void	free_cube(t_cube *cube);
int	ft_isspace(int c);
void render(t_cube *cube);
void raycast(t_cube *cube);
void texture(t_game *game, t_values *values, int side, double perp_dist, int line_h, int start, int end, int x);
void draw_ceil_floor(t_game *game, int x, int start, int end, int screen_h);

#endif