NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = raycasting.c calculate.c main.c render_utils.c color.c \
		key_loop_control.c movement.c rotate.c file_check.c \
		free.c get_next_line.c map_check.c map.c space_check.c \
		texture_parser.c texture.c utils.c player.c ft_printf.c

OBJ = $(SRC:.c=.o)

MLX_DIR = mlx
LIBFT_DIR = libft

MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

INCLUDES = -I/usr/include -I$(MLX_DIR) -I$(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(MLX_DIR)
	make -C $(LIBFT_DIR)
	$(CC) $(OBJ) $(LIBFT_FLAGS) $(MLX_FLAGS) -o $(NAME)

clean:
	rm -f $(OBJ)
	make clean -C $(MLX_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re