/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:52:30 by adapassa          #+#    #+#             */
/*   Updated: 2024/04/18 15:03:24 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	flood_fill(char *map, t_vars vars, int pos, int *flag)
{
	if (map[pos + 1] == 'E' || map[pos - 1] == 'E'
		|| map[pos - vars.map_width] == 'E'
		|| map[pos + vars.map_width] == 'E')
		*flag = 1;
	if (map[pos + 1] == '0' || map[pos + 1] == 'C')
	{
		map[pos] = 'F';
		flood_fill(map, vars, pos + 1, flag);
	}
	if (map[pos + vars.map_width] == '0'
		|| map[pos + vars.map_width] == 'C')
	{
		map[pos] = 'F';
		flood_fill(map, vars, pos + vars.map_width, flag);
	}
	if (map[pos - 1] == '0' || map[pos - 1] == 'C')
	{
		map[pos] = 'F';
		flood_fill(map, vars, pos - 1, flag);
	}
	if (map[pos - vars.map_width] == '0' || map[pos - vars.map_width] == 'C')
	{
		map[pos] = 'F';
		flood_fill(map, vars, pos - vars.map_width, flag);
	}
}

bool	check_borders(t_vars *vars, char *tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (vars->map_no_nl[j] != '\0')
		j++;
	while (i < vars->map_width)
	{
		if (vars->map_no_nl[i] != '1')
		{
			ft_putstr_fd("error with map borders!\n", 2);
			free(tmp);
			free_exit(vars);
		}
		i++;
	}
	if (helper1(vars, i, j) != 0)
	{
		ft_putstr_fd("error with map borders!\n", 2);
		free(tmp);
		free_exit(vars);
	}
	return (false);
}

void	free_exit(t_vars *vars)
{
	free(vars->map);
	free(vars->map_no_nl);
	mlx_destroy_image(vars->mlx, vars->img_ptr);
	mlx_destroy_image(vars->mlx, vars->wall_ptr);
	mlx_destroy_image(vars->mlx, vars->coin);
	mlx_destroy_image(vars->mlx, vars->exit);
	if (vars->player_image != NULL)
		mlx_destroy_image(vars->mlx, vars->player_image);
	mlx_clear_window(vars->mlx, vars->win);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(0);
}

