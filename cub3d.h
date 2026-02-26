/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eakkoc <eakkoc@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 17:44:40 by udemirci          #+#    #+#             */
/*   Updated: 2026/02/26 20:58:22 by eakkoc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "get_next_line.h"
# include "libft/libft.h"
# include "mlx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef SCREENW
#  define SCREENW 800
# endif

# ifndef SCREENH
#  define SCREENH 800
# endif

typedef struct s_values
{
	double		cam_x;
	double		plane_x;
	double		plane_y;
	double		dir_x;
	double		dir_y;
	double		raydir_x;
	double		raydir_y;
	double		delta_x;
	double		delta_y;
	double		spos_x;
	double		spos_y;
	double		perp_x;
	double		perp_y;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			line_h;
	int			start;
	int			end;
	int			x;
	int			side;
	int			selected_x;
}				t_values;

typedef struct s_game
{
	int			w_key;
	int			a_key;
	int			s_key;
	int			d_key;
	int			left_key;
	int			right_key;
	void		*img;
	int			*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	double		posx;
	double		posy;
	double		angle;
	void		*mlx;
	void		*win;
	void		*no;
	void		*so;
	void		*we;
	void		*ea;
	int			*no_data;
	int			*so_data;
	int			*we_data;
	int			*ea_data;
	int			tex_w;
	int			tex_h;
	char		**map;
}				t_game;

typedef struct s_player
{
	int			x;
	int			y;
	char		dir;
}				t_player;

typedef struct s_text
{
	char		**colour;
	char		*ea;
	char		*we;
	char		*no;
	char		*so;
	int			fd;
	int			floor;
	int			ceiling;
	int			f_check;
	int			c_check;
}				t_text;

typedef struct s_map
{
	char		**maps;
	char		**n_maps;
	int			height;
	int			map_start;

}				t_map;

typedef struct s_cube
{
	t_map		map;
	int			fd;
	int			mapline;
	t_text		text;
	char		**lines;
	t_player	player;
	t_game		*game;
}				t_cube;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char			*get_next_line(int fd);
char			*ft_strtrim(char const *s1, char const *set);
int				parse_colour(t_cube *cube, char *line);
int				ft_isspace(int c);
void			render(t_cube *cube);
void			raycast(t_cube *cube);
void			texture(t_game *game, t_values *values, double perp_dist);
void			draw_ceil_floor(t_cube *cube, int x, int start, int end);
void			load_textures(t_cube *cube);
void			start_raycasting(t_cube *cube);
int				key_press(int keycode, t_cube *cube);
int				key_release(int keycode, t_cube *cube);
int				handle_player_move(t_cube *cube);
int				handle_player_rotate(t_cube *cube);
int				game_loop(t_cube *cube);
void			move_backward(t_game *game);
void			move_forward(t_game *game);
void			move_left(t_game *game);
void			move_right(t_game *game);
void			rotate_right(t_game *game);
void			rotate_left(t_game *game);
int				ft_isspace(int c);
void			free_cube(t_cube *cube, char *msg);
int				check_map_after(t_cube *cube);
int				up_down_check(t_cube *cube);
int				check_sides(t_cube *cube);
int				locate_player(t_cube *cube);
int				texture_check(t_cube *cube, char *line);
int				check_path(t_cube *cube, char *path);
void			read_lines(t_cube *cube, char *path);
int				is_valid(char c);
int				is_char(char c);
int				is_maps_line(char *line);
int				is_map_line(char *line);
void			count_map_height(t_cube *cube);
void			fill_map_n(t_cube *cube, int i);
void			fill_map(t_cube *cube, int i);
int				map_alloc(t_cube *cube);
int				handle_space_player(t_cube *cube);
void			handle_space(t_cube *cube);
int				zero_check(t_cube *cube);
void			init_textures(t_cube *cube);
void			find_map_start(t_cube *cube);
double			perp_dist(t_values values, int side);
int				close_window(t_cube *cube);
void			free_colour(t_cube *cube);
void			destroy_textures(t_cube *cube);
void			free_game(t_cube *cube, char *msg);
#endif