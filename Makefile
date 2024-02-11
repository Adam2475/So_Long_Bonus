CC = cc
NAME = so_long.exe
FLAGS =  -g
SRC = main.c src/commands.c src/parsing.c \
		src/rendering.c \

OBJ = $(SRC:.c=.o)
LIB = mlx_linux/libmlx_Linux.a -lXext -lm
MLX = mlx_linux
LIB = libft.a

all: $(NAME)

$(NAME): $(OBJ)
		@cd libft/ && $(MAKE) && mv $(LIB) ../
		@$(MAKE) -C $(MLX)
		$(CC) $(FLAGS) $(SRC) $(LIB) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME) 

clean:
		rm -f $(OBJ)
		@cd libft && $(MAKE) clean
		@cd $(MLX) && $(MAKE) clean

fclean: clean
		rm -f $(LIB)
		rm -f $(NAME)

re: fclean  all