// #include "a.h"
#include "cub3d.h"

void draw_ceil_floor(t_game *game, int x, int start, int end, int screen_h)
{
    int y;

    y = 0;
    while (y < start)
    {
        mlx_pixel_put(game->mlx, game->win, x, y, 0x335553);
        y++;
    }
    y = end;
    while (y < screen_h)
    {
        mlx_pixel_put(game->mlx, game->win, x, y, 0x7666677);
        y++;
    }
}