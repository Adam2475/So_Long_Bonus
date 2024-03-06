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
	int		counter;
	int		total_collectable;
	int		taken_collectable;
	char	*map_no_nl;
	int		pos_i;
}	t_vars;

int 	key_hook(int keycode, t_vars *vars);
int		map_error(char *map, t_vars *vars);
char 	*clone_map(char *map);
void	render_map(t_vars *vars, char *relative_path, char *wall_path, char *coin_ptr, char *exit_ptr);
void	*render_player(t_vars *vars, char *map, char *path);
void	check_movement(int keycode, t_vars *vars);
void	flood_fill(char *map, t_vars vars, int position, int *flag);
bool	check_borders(t_vars vars);
char	*restock_map(char *map);
void	free_exit(t_vars *vars);

#endif
