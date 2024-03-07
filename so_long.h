/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:36:25 by adapassa          #+#    #+#             */
/*   Updated: 2024/03/07 16:34:36 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdio.h>
# include "libft/libft.h"
# include "mlx_linux/mlx.h"

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
	int		img_width;
	int		img_height;
	void	*img_ptr;
	void	*wall_ptr;
	void	*coin;
	void	*exit;
}	t_vars;

int 	key_hook(int keycode, t_vars *vars);
int		map_error(char *map, t_vars *vars);
char 	*clone_map(char *map);
void	render_map(t_vars *vars);
void	*render_player(t_vars *vars, char *map, char *path);
void	check_movement(int keycode, t_vars *vars);
void	flood_fill(char *map, t_vars vars, int position, int *flag);
bool	check_borders(t_vars vars);
char	*restock_map(char *map);
void	free_exit(t_vars *vars);
bool	check_position(t_vars *vars, char *map, int position, int direction);
bool	take_coin(t_vars *vars, char *map, int tmp);
char	*helper3(char *map, int height);
bool	helper1(t_vars vars, int i, int j, int y);

#endif
