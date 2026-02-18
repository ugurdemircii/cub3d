NAME = cub3d

CC = cc
CFLAGS =
SRC = a.c b.c texture.c  main.c çalma_gnl.c ceil.c color.c
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
