/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_loop_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udemirci <udemirci@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 17:45:55 by udemirci          #+#    #+#             */
/*   Updated: 2026/02/27 01:58:11 by udemirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_cube *cube)
{
	if (keycode == 119)
		cube->game->w_key = 1;
	if (keycode == 97)
		cube->game->a_key = 1;
	if (keycode == 115)
		cube->game->s_key = 1;
	if (keycode == 100)
		cube->game->d_key = 1;
	if (keycode == 65361)
		cube->game->left_key = 1;
	if (keycode == 65363)
		cube->game->right_key = 1;
	if (keycode == 65307)
		free_game(cube, "");
	return (0);
}

int	key_release(int keycode, t_cube *cube)
{
	if (keycode == 119)
		cube->game->w_key = 0;
	if (keycode == 97)
		cube->game->a_key = 0;
	if (keycode == 115)
		cube->game->s_key = 0;
	if (keycode == 100)
		cube->game->d_key = 0;
	if (keycode == 65361)
		cube->game->left_key = 0;
	if (keycode == 65363)
		cube->game->right_key = 0;
	return (0);
}

static int	handle_player_move(t_cube *cube)
{
	int	moved;

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

static int	handle_player_rotate(t_cube *cube)
{
	int	moved;

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

int	game_loop(t_cube *cube)
{
	int	moved;

	moved = 0;
	if (handle_player_move(cube))
		moved = 1;
	if (handle_player_rotate(cube))
		moved = 1;
	if (moved)
		start_raycasting(cube);
	return (0);
}
