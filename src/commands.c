/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:06:05 by adapassa          #+#    #+#             */
/*   Updated: 2024/04/15 10:59:31 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
#include "../mlx_linux/mlx.h"

int	exit_hook(t_vars *vars, int x_event,
		int (*funct)(), void *param)
{
	ft_printf("Window Closed\n");
	free_exit(vars);
	return (0);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == ESC_KEY || keycode == 17)
	{
		ft_printf("Window Closed\n");
		free_exit(vars);
	}
	if (keycode == ARR_LEFT || keycode == ARR_RIGHT
		|| keycode == ARR_UP || keycode == ARR_DOWN)
	{
		check_movement(keycode, vars);
	}
	render_map(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->player_image,
		vars->pos_x * TILE_SIZE, vars->pos_y * TILE_SIZE);
	return (0);
}

bool	take_coin(t_vars *vars, char *map, int tmp)
{
	vars->taken_collectable++;
	ft_printf("collected coins: %d\n", vars->taken_collectable);
	ft_printf("collectable taken\n");
	map[tmp] = '0';
	return (false);
}

static	void	executor(int flag, t_vars *vars)
{
	if (flag == 0)
	{
		vars->pos_x--;
		ft_printf("%d\n", vars->counter++);
		vars->player_i = vars->player_i - 1;
	}
	else if (flag == 1)
	{
		vars->pos_x++;
		ft_printf("%d\n", vars->counter++);
		vars->player_i = vars->player_i + 1;
	}
	else if (flag == 2)
	{
		vars->pos_y--;
		ft_printf("%d\n", vars->counter++);
		vars->player_i = vars->player_i - vars->map_width;
	}
	else if (flag == 3)
	{
		vars->pos_y++;
		ft_printf("%d\n", vars->counter++);
		vars->player_i = vars->player_i + vars->map_width;
	}
}

void	check_movement(int keycode, t_vars *vars)
{
	if (keycode == ARR_LEFT)
	{
		if (check_position(vars, vars->map, vars->player_i, LEFT) == false)
			executor(0, vars);
	}
	if (keycode == ARR_RIGHT)
	{
		if (check_position(vars, vars->map, vars->player_i, RIGHT) == false)
			executor(1, vars);
	}
	if (keycode == ARR_UP)
	{
		if (check_position(vars, vars->map, vars->player_i - 1, UP) == false)
			executor(2, vars);
	}
	if (keycode == ARR_DOWN)
	{
		if (check_position(vars, vars->map, vars->player_i, DOWN) == false)
			executor(3, vars);
	}
}
