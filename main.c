/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:48:32 by adapassa          #+#    #+#             */
/*   Updated: 2024/03/05 19:45:18 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx_linux/mlx.h"
#include <time.h>

//sudo apt install libx11-dev 
//libxext-dev

void free_exit(t_vars *vars)
{
	free(vars->map);
	free(vars->map_no_nl);
	//free(vars->player_image);
	exit(0);
}

char *restock_map(char *map)
{
	int i = 0;
	int x = 0;
	char *tmp;
	int j = 0;
	int height = 0;

	while (map[i] != '\0')
	{
		if (map[i] == '\n')
			height++;
		i++;
	}
	i = 0;

	tmp = (char *)malloc(sizeof(char) * (ft_strlen(map) - height + 1));

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
	}
	i = i - height;
	tmp[i] = '\0';
	return (tmp);
}

static void struct_init(t_vars *vars)
{
	vars->mlx = NULL;
	vars->win = NULL;
	vars->map = NULL;
	vars->map_width = 0;
	vars->map_height = 0;
	vars->player_i = 0;
	vars->pos_x = 0;
	vars->pos_y = 0;
	vars->player_image = NULL;
	vars->counter = 0;
	vars->total_collectable = 0;
	vars->taken_collectable = 0;
	vars->map_no_nl = NULL;
	vars->pos_i = 0;
}

int main(int ac, char **av)
{
	t_vars		vars;
	int			i = 0;
	int			x = 0;
	int			flag = 0;
	char		*tmp;

	struct_init(&vars);
	vars.map = clone_map(av[1]);
	vars.map_no_nl = restock_map(vars.map);
	tmp = restock_map(vars.map);

	while (vars.map[x] != '\n')
		x++;
	while (vars.map_no_nl[i] != 'P')
		i++;
	vars.pos_i = i;
	i = 0;
	vars.map_width = 0;
	vars.map_width = x;
	flood_fill(vars.map_no_nl, vars, vars.pos_i, &flag);

    //if (ac != 2)
    //	return (ft_putstr_fd("Error! Wrong number of arguments!\n", 2));
    if (map_error(vars.map, &vars) == TRUE)
    	return (ft_putstr_fd("Error! Unrecognized symbol in map!\n", 2));
	if (check_borders(vars) != false)
		return (ft_putstr_fd("Error! Map not delimited by walls!\n", 2));
	if (flag <= 0)
		return (ft_putstr_fd("Error! No path to exit in selected map!\n", 2));
	
    vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 640, 480, "So_Long");
	vars.counter = 0;
	mlx_key_hook(vars.win, &key_hook, &vars);
	render_map(&vars, vars.map, "./img/grass.xpm", "./img/wall.xpm", "./img/coin.xpm",  "./img/exit.xpm");
	render_player(&vars, vars.map, "./img/chara.xpm");
	mlx_loop(vars.mlx);
	//free(vars.map);
	//free(vars.map_no_nl);
    return (0);
}
