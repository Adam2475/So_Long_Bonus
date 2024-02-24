/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:48:32 by adapassa          #+#    #+#             */
/*   Updated: 2024/02/24 20:40:11 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx_linux/mlx.h"
#include <time.h>

//sudo apt install libx11-dev 
//libxext-dev

static char *restock_map(char *map)
{
	int i = 0;
	int x = 0;
	char *tmp;
	tmp = (char *)malloc(sizeof(char) * ft_strlen(map));

	while (map[i] != '\0')
	{
		if (map[i] != '\n')
		{
			tmp[x] = map[i];
			i++;
			x++;
		}
		else
			i++;
	return (tmp);
}

int main(int ac, char **av)
{
	t_vars		vars;
	int i = 0;
	int x = 0;

	vars.total_collectable = 0;
	vars.taken_collectable = 0;
	vars.map = clone_map(av[1]);

	vars.map_no_nl = restock_map(vars.map);

	while (vars.map[x] != '\n')
		x++;

	while (vars.map[vars.pos_i] != 'P' && vars.map[vars.pos_i] != '\0')
    	vars.pos_i++;

	vars.map_width = x;

    if (ac != 2)
    	return (ft_putstr_fd("Error! Wrong number of arguments!\n", 2));
    if (map_error(vars.map, &vars) == TRUE)
    	return (ft_putstr_fd("Error! Unrecognized symbol in map!\n", 2));
	if (check_borders(vars.map_no_nl, vars) != false)
		return (ft_putstr_fd("Error! Map not delimited by walls!\n", 2));
	if (flood_fill(vars.map_no_nl, vars, vars.pos_i) != false)
		return (ft_putstr_fd("Error! No path to exit in selected map!\n", 2));
	
    vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 640, 480, "So_Long");
	vars.counter = 0;

	mlx_key_hook(vars.win, &key_hook, &vars);

	render_map(&vars, vars.map, "./img/grass.xpm", "./img/wall.xpm", "./img/coin.xpm",  "./img/exit.xpm");

	render_player(&vars, vars.map, "./img/chara.xpm");
	
	mlx_loop(vars.mlx);
    return (0);
}