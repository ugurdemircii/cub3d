NAME = cub3D

CC = cc
CFLAGS =
SRC = raycasting.c calculate.c  main.c  ceil_floor.c color.c key_loop_control.c movement.c rotate.c \
		file_check.c free.c get_next_line.c map_check.c map.c space_check.c texture_parser.c texture.c utils.c
OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC)  -I/usr/include -Imlx_linux -g3 -O3 -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	make -C mlx_linux
	make -C libft
	$(CC) $(OBJ) -Llibft -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean:
	rm -rfv $(OBJ)
	make clean -C mlx_linux
	make clean -C libft

fclean: clean
	rm -rfv $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
