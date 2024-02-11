/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:48:32 by adapassa          #+#    #+#             */
/*   Updated: 2024/02/06 21:46:04 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx_linux/mlx.h"

//sudo apt install libx11-dev 
//libxext-dev

int main(int ac, char **av)
{
	char 		*map;
	t_vars		vars;

	vars.map = clone_map(av[1]);
    if (ac != 2)
    	return (ft_putstr_fd("Error! Wrong number of arguments!\n", 2));
    if (map_error(av[1]) != 1)
    	return (ft_putstr_fd("Error! Unrecognized symbol in map!\n", 2));
	
    vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 640, 480, "So_Long");

	render_map(&vars, vars.map, "./img/grass.xpm", "./img/wall.xpm");
	render_player(&vars, vars.map, "./img/chara.xpm");

	ft_printf("%d\n", vars.pos_x);
	ft_printf("%d\n", vars.pos_y);

	mlx_key_hook(vars.win, &key_hook, &vars);

	mlx_loop(vars.mlx);
    return (0);
}