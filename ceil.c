#include "cub3d.h"

void draw_ceil_floor(t_cube *cube, int x, int start, int end)
{
    int y;

    y = 0;
    while (y < start)
    {
        cube->game->addr[y * (cube->game->line_length / 4) + x] = cube->text.ceiling;
        y++;
    }
    y = end;
    while (y < SCREENH)
    {
        cube->game->addr[y * (cube->game->line_length / 4) + x] = cube->text.floor;
        y++;
    }
}
