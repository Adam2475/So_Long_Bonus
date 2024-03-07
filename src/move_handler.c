/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:20:35 by adapassa          #+#    #+#             */
/*   Updated: 2024/03/07 15:39:12 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static bool check_left(t_vars *vars, char *map, int position, int direction)
{
    int tmp;

    tmp = 0;
    if (map[position + (vars->pos_y - 1) - 1] != '1')
	{
		if (map[position + (vars->pos_y - 1) - 1] == 'C')
		{
			tmp = position + (vars->pos_y - 1) - 1;
			take_coin(vars, map, tmp);
		}
		else if (map[position - 1 + (vars->pos_y - 1)] == 'E' && vars->taken_collectable == vars->total_collectable)
		{
			ft_printf("yeeee you finished!");
			free_exit(vars);
		}
		if (map[position + (vars->pos_y - 1) - 1] == 'E')
			return (true);
		return (false);
	}
}

static bool check_right(t_vars *vars, char *map, int position, int direction)
{
    int tmp;

    tmp = 0;
    if (map[position + (vars->pos_y - 1) + 1] != '1')
	{
		if (map[position + (vars->pos_y - 1) + 1] == 'C')
		{
			tmp = position + (vars->pos_y - 1) + 1;
			take_coin(vars, map, tmp);
		}
		else if (map[position + 1 + (vars->pos_y - 1)] == 'E' && vars->taken_collectable == vars->total_collectable)
		{
			ft_printf("yeeee you finished!");
			free_exit(vars);
		}
		if (map[position + (vars->pos_y - 1) + 1] == 'E')
			return (true);
		return (false);
	}
}

static bool check_up(t_vars *vars, char *map, int position, int direction)
{
    int tmp;

    tmp = 0;
    if (map[position - vars->map_width + (vars->pos_y - 1)] != '1' )
	{
		if (map[position - vars->map_width + (vars->pos_y - 1)] == 'C')
		{
			tmp = position - vars->map_width + (vars->pos_y - 1);
			take_coin(vars, map, tmp);
		}
		else if (map[position - vars->map_width + (vars->pos_y - 1)] == 'E' && vars->taken_collectable == vars->total_collectable)
		{
			ft_printf("yeeee you finished!");
			free_exit(vars);
		}
		else if (map[position - vars->map_width + (vars->pos_y - 1)] == 'E')
			return (true);
		return (false);
	}
}

static bool check_down(t_vars *vars, char *map, int position, int direction)
{
    int tmp;

    tmp = 0;
    if (map[position + vars->map_width + vars->pos_y] != '1')
	{
		if (map[position + vars->map_width + vars->pos_y] == 'C')
		{
			tmp = position + vars->map_width + vars->pos_y;
			take_coin(vars, map, tmp);
		}
		else if (map[position + vars->map_width + (vars->pos_y)] == 'E' && vars->taken_collectable == vars->total_collectable)
		{
			ft_printf("yeeee you finished!");
			free_exit(vars);
		}
		if (map[position + vars->map_width + vars->pos_y] == 'E')
			return (true);
		return (false);
	}
}

bool	check_position(t_vars *vars, char *map, int position, int direction)
{
	
	if (direction == UP)
	{
		if (check_up(vars, map, position, direction) == false)
			return (false);
	}
	else if (direction == DOWN)
	{
		if (check_down(vars, map, position, direction) == false)
			return (false);
	}
	else if (direction == LEFT)
	{
		if (check_left(vars, map, position, direction) == false)
			return (false);
	}
	else if (direction == RIGHT)
	{
		if (check_right(vars, map, position, direction) == false)
			return (false);
	}
	return (true);
}