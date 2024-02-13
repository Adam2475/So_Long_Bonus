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
	if (keycode == ARR_LEFT || keycode == ARR_RIGHT
		|| keycode == ARR_UP || keycode == ARR_DOWN)
	{
		check_movement(keycode, vars);
	}

	mlx_clear_window(vars->mlx, vars->win);
	render_map(vars, vars->map, "./img/grass.xpm", "./img/wall.xpm");
	mlx_put_image_to_window(vars->mlx, vars->win, vars->player_image, vars->pos_x * TILE_SIZE,  vars->pos_y * TILE_SIZE);
	//render_re(vars, chara, vars->map, "./img/chara.xpm");

	return (0);
}

static bool	check_position(t_vars vars, char *map, int position, int direction)
{
	if (direction == UP)
	{
		if (map[position - vars.map_width] != '1')
		{
			return (false);
		}
	}
	else if (direction == DOWN)
	{
		if (map[position + vars.map_width] != '1')
		{
			return (false);
		}
	}
	else if (direction == LEFT)
	{
		if (map[position - 1] != '1')
		{
			return (false);
		}
	}
	else if (direction == RIGHT)
	{
		if (map[position + 1] != '1')
		{
			return (false);
		}
	}
	return (true);
}

//bool is_valid_movement()

void check_movement(int keycode, t_vars *vars)
{
	int tmp;
	int jmp;

	tmp = vars->pos_x;
	jmp = vars->pos_x;

	if (keycode == ARR_LEFT)
	{
		
		if (check_position(*vars, vars->map, vars->player_i, LEFT) == false)
		{
			vars->pos_x--;
			ft_printf("%d\n", vars->pos_x);
			vars->player_i = vars->player_i - 1;
		}
		else
			ft_printf("Bang!\n");
	}
	if (keycode == ARR_RIGHT)
	{
		if (check_position(*vars, vars->map, vars->player_i, RIGHT) == false)
		{
			//ft_printf("%d\n", check_position(*vars, vars->map, vars->player_i, RIGHT));
			vars->pos_x++;
			ft_printf("%d\n", vars->pos_x);
			vars->player_i = vars->player_i + 1;
		}
		else
			ft_printf("Bang!\n");
	}
	if (keycode == ARR_UP)
	{
		if (check_position(*vars, vars->map, vars->player_i, UP) == false)
		{
			vars->pos_y--;
			ft_printf("%d\n", vars->pos_y);
			vars->player_i = vars->player_i - vars->map_width;
		}
		else
			ft_printf("Bang!\n");
	}
	if (keycode == ARR_DOWN)
	{
		if (check_position(*vars, vars->map, vars->player_i, DOWN) == false)
		{
			vars->pos_y++;
			ft_printf("%d\n", vars->pos_y);
			vars->player_i = vars->player_i + vars->map_width;
		}
		else
			ft_printf("Bang!\n");
	}
}