#include "cub3d.h"


int is_wall(double x, double y, char **map)
{
    int mapx = (int)((x) / 64);
    int mapy = (int)((y) / 64);
    
    if (map[mapy][mapx] == '1')
    return 1;
    return 0;
}


void move_backward(t_game *game)
{
    double newx = game->posx - cos(game->angle) * 3;
    double newy = game->posy - sin(game->angle) * 3;

    if (!is_wall(newx, game->posy, game->map))
        game->posx = newx;
    if (!is_wall(game->posx, newy, game->map))
        game->posy = newy;
}


void move_forward(t_game *game)
{
    double newx = game->posx + cos(game->angle) * 3;
    double newy = game->posy + sin(game->angle) * 3;

    if (!is_wall(newx, game->posy, game->map))
        game->posx = newx;
    if (!is_wall(game->posx, newy, game->map))
        game->posy = newy;
}

void move_left(t_game *game)
{
    double newx = game->posx + cos(game->angle - M_PI / 2.0) * 3;
    double newy = game->posy + sin(game->angle - M_PI / 2.0) * 3;

    if (!is_wall(newx, game->posy, game->map))
        game->posx = newx;
    if (!is_wall(game->posx, newy, game->map))
        game->posy = newy;
}

void move_right(t_game *game)
{
    double newx = game->posx + cos(game->angle + M_PI / 2.0) * 3;
    double newy = game->posy + sin(game->angle + M_PI / 2.0) * 3;

    if (!is_wall(newx, game->posy, game->map))
        game->posx = newx;
    if (!is_wall(game->posx, newy, game->map))
        game->posy = newy;
}