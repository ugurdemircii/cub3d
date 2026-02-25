#include "cub3d.h"

void rotate_left(t_game *game)
{
    game->angle -= 0.01;
}

void rotate_right(t_game *game)
{
    game->angle += 0.01;
}
