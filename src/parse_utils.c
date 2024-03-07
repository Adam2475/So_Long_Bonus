/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:52:30 by adapassa          #+#    #+#             */
/*   Updated: 2024/03/07 14:58:32 by adapassa         ###   ########.fr       */
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

bool	check_borders(t_vars vars)
{
	int	i;
	int	j;
	int	y;

	i = 0;
	j = 0;
	y = 0;
	while (vars.map[y] != '\0')
	{
		if (vars.map[y] == '\n')
			j++;
		y++;
	}
	if (!vars.map_no_nl)
		return (true);
	vars.map_height = j;
	while (vars.map_no_nl[i] && vars.map_no_nl[i] != '\0')
	{
		if (helper1(vars, i, j, y) == false)
			return (false);
		else
			return (true);
	}
	return (false);
}
