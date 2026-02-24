#include "cub3d.h"

int key_press(int keycode, t_cube *cube)
{
    if (keycode == 13)
        cube->game->w_key = 1;
    if (keycode == 0)
        cube->game->a_key = 1;
    if (keycode == 1)
        cube->game->s_key = 1;
    if (keycode == 2)
        cube->game->d_key = 1;
    if (keycode == 123)
        cube->game->left_key = 1;
    if (keycode == 124)
        cube->game->right_key = 1;
    if (keycode == 53)
        exit(0);
    return (0);
}

int key_release(int keycode, t_cube *cube)
{
    if (keycode == 13)
        cube->game->w_key = 0;
    if (keycode == 0)
        cube->game->a_key = 0;
    if (keycode == 1)
        cube->game->s_key = 0;
    if (keycode == 2)
        cube->game->d_key = 0;
    if (keycode == 123)
        cube->game->left_key = 0;
    if (keycode == 124)
        cube->game->right_key = 0;
    return (0);
}

int handle_player_move(t_cube *cube)
{
    int moved;

    moved = 0;
    if (cube->game->w_key)
    {
        move_forward(cube->game);
        moved = 1;
    }
    if (cube->game->s_key)
    {
        move_backward(cube->game);
        moved = 1;
    }
    if (cube->game->a_key)
    {
        move_left(cube->game);
        moved = 1;
    }
    if (cube->game->d_key)
    {
        move_right(cube->game);
        moved = 1;
    }
    return (moved);
}

int handle_player_rotate(t_cube *cube)
{
    int moved;

    moved = 0;
    if (cube->game->left_key)
    {
        rotate_left(cube->game);
        moved = 1;
    }
    if (cube->game->right_key)
    {
        rotate_right(cube->game);
        moved = 1;
    }
    return (moved);
}


int game_loop(t_cube *cube)
{
    int moved;

    moved = 0;
    if (handle_player_move(cube))
        moved = 1;
    if (handle_player_rotate(cube))
        moved = 1;
    if (moved)
        start_raycasting(cube);
    return (0);
}
