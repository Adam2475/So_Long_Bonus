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
	mlx_destroy_image(vars->mlx, vars->img_ptr);
	mlx_destroy_image(vars->mlx, vars->wall_ptr);
	mlx_destroy_image(vars->mlx, vars->coin);
	mlx_destroy_image(vars->mlx, vars->exit);
	mlx_destroy_image(vars->mlx, vars->player_image);
	mlx_clear_window(vars->mlx, vars->win);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
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

static void struct_init(t_vars *vars, char *av)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, 640, 480, "So_Long");
	vars->map = clone_map(av);
	vars->map_width = 0;
	vars->map_height = 0;
	vars->player_i = 0;
	vars->pos_x = 0;
	vars->pos_y = 0;
	vars->player_image = NULL;
	vars->counter = 1;
	vars->total_collectable = 0;
	vars->taken_collectable = 0;
	vars->map_no_nl = restock_map(vars->map);
	vars->pos_i = 0;
	vars->img_height = 32;
	vars->img_width = 32;
	vars->img_ptr = mlx_xpm_file_to_image(vars->mlx, "./img/grass.xpm", &vars->img_width, &vars->img_height);
	vars->wall_ptr = mlx_xpm_file_to_image(vars->mlx, "./img/wall.xpm", &vars->img_width, &vars->img_height);
	vars->coin = mlx_xpm_file_to_image(vars->mlx, "./img/coin.xpm", &vars->img_width, &vars->img_height);
	vars->exit = mlx_xpm_file_to_image(vars->mlx, "./img/exit.xpm", &vars->img_width, &vars->img_height);
}

int main(int ac, char **av)
{
	t_vars		vars;
	int			i = 0;
	int			x = 0;
	int			flag = 0;
	char		*tmp;

	struct_init(&vars, av[1]);
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
	if (ac != 2)
		return (ft_putstr_fd("Error! Wrong number of arguments!\n", 2));
	if (map_error(vars.map, &vars) == TRUE)
		return (ft_putstr_fd("Error! Unrecognized symbol in map!\n", 2));
	if (check_borders(vars) != false)
		return (ft_putstr_fd("Error! Map not delimited by walls!\n", 2));
	if (flag <= 0)
		return (ft_putstr_fd("Error! No path to exit in selected map!\n", 2));
	free(tmp);
	mlx_key_hook(vars.win, &key_hook, &vars);
	render_map(&vars);
	render_player(&vars, vars.map, "./img/chara.xpm");
	ft_printf("collectables on map: %d\n", vars.total_collectable);
	mlx_loop(vars.mlx);
	return (0);
}
