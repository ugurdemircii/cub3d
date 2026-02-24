NAME = cub3D

CC = cc
CFLAGS =
SRC = raycasting.c calculate.c  main.c  ceil_floor.c color.c key_loop_control.c movement.c rotate.c \
		file_check.c free.c get_next_line.c map_check.c map.c space_check.c texture_parser.c texture.c utils.c
OBJ = $(SRC:.c=.o)

MLX = -framework OpenGL -framework AppKit -lmlx
MLX_DIR = mlx
INCLUDES = -I $(MLX_DIR)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(INCLUDES)  -L $(MLX_DIR) $(MLX) ./libft/libft.a -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
