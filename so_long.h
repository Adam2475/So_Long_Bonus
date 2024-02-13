#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdio.h>
# include "libft/libft.h"

# define TRUE 1
# define FALSE 0
# define TILE_SIZE 32
# define ESC_KEY 65307
# define ARR_LEFT 65361
# define ARR_RIGHT 65363
# define ARR_UP 65362
# define ARR_DOWN 65364

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	char	*map;
	int		map_width;
	int		map_height;
	int		player_i;
	int		pos_x;
	int		pos_y;
	void	*player_image;
}	t_vars;

int 	key_hook(int keycode, t_vars *vars);
int		map_error(char *map);
char 	*clone_map(char *map);
void	render_map(t_vars *vars, char *map, char *relative_path, char *wall_path);
void	*render_player(t_vars *vars, char *map, char *path);
void	check_movement(int keycode, t_vars *vars);

#endif