#ifndef A_H
# define A_H
# include <math.h>
# include "mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
typedef struct s_game
{
    int posx;
    int posy;
    double angle;
    void *mlx;
    void *win;
    char **map;
}t_game;

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


void raycast(t_game *game);

#endif