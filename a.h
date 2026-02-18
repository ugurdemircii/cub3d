#ifndef A_H
# define A_H

# include "cub3d.h"

typedef struct s_game
{
    int posx;
    int posy;
    double angle;
    void *mlx;
    void *win;
    char **map;
}t_game;





#endif