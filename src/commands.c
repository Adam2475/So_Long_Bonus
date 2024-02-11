#include "../so_long.h"
#include "../mlx_linux/mlx.h"

int key_hook(int keycode, t_vars *vars)
{
	if (keycode == ESC_KEY)
	{
		mlx_destroy_window(vars->mlx, vars->win);
	 	ft_printf("Window Closed\n");
		exit(0);
	}
	if (keycode == ARR_LEFT)
	{
		vars->pos_x--;
	}
	if (keycode == ARR_RIGHT)
	{
		vars->pos_x++;
	}
	if (keycode == ARR_UP)
	{
		vars->pos_y--;
	}
	if (keycode == ARR_DOWN)
	{
		vars->pos_y++;
	}

	mlx_clear_window(vars->mlx, vars->win);

	render_map(vars, vars->map, "./img/grass.xpm", "./img/wall.xpm");
	mlx_put_image_to_window(vars->mlx, vars->win, vars->player_image, vars->pos_x * TILE_SIZE,  vars->pos_y * TILE_SIZE);
	//render_re(vars, chara, vars->map, "./img/chara.xpm");

	return (0);
}