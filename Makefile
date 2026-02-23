NAME = cub3d

CC = cc
CFLAGS = #-Wall -Wextra -Werror 
SRC = main.c color.c get_next_line.c free.c map_check.c \
		texture.c utils.c file_check.c map.c \
		space_check.c 
OBJ = $(SRC:.c=.o)


all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) libft/libft.a -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re