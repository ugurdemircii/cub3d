NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = raycasting.c calculate.c main.c render_utils.c color.c \
		key_loop_control.c movement.c rotate.c file_check.c \
		free.c get_next_line.c map_check.c map.c space_check.c \
		texture_parser.c texture.c utils.c player.c ft_printf.c

OBJS = $(SRCS:.c=.o)

MLX_DIR = mlx
LIBFT_DIR = libft

MLX = $(MLX_DIR)/libmlx_Linux.a
LIBFT = $(LIBFT_DIR)/libft.a

LDFLAGS = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz \
		  -L$(LIBFT_DIR) -lft


all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	make -C $(MLX_DIR)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

clean:
	rm -f $(OBJS)
	make -C $(MLX_DIR) clean
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re