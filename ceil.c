// #include "a.h"
#include "cub3d.h"

void draw_ceil_floor(t_cube *cube, int x, int start, int end, int screen_h)
{
    int y;

    y = 0;
    while (y < start)
    {
        mlx_pixel_put(cube->game->mlx, cube->game->win, x, y, cube->text.ceiling);
        y++;
    }
    y = end;
    while (y < screen_h)
    {
        mlx_pixel_put(cube->game->mlx, cube->game->win, x, y, cube->text.floor);
        y++;
    }
}
