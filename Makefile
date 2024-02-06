CC = cc
NAME = so_long.exe
SRC = main.c
OBJ = $(SRC:.c=.o)
LIB = mlx_linux/libmlx_Linux.a -lXext -lm
MLX = mlx_linux

all: $(NAME)

$(NAME): $(OBJ)
#		$(MAKE) -s -C $(MLX)
		$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean:
		rm -f $(OBJ)

flean: clean
		make clean -C $(MLX)
		rm -rf $(NAME)

re: fclean all