/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:48:32 by adapassa          #+#    #+#             */
/*   Updated: 2024/04/18 15:18:40 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static	void	check_collectables(char *str, t_vars *vars, char *tmp)
{
	int	i;

	i = 0;
	free(tmp);
	while (str[i] != '\0')
	{
		if (str[i] == 'C')
		{
			free(vars->map);
			free(vars->map_no_nl);
			mlx_destroy_image(vars->mlx, vars->img_ptr);
			mlx_destroy_image(vars->mlx, vars->wall_ptr);
			mlx_destroy_image(vars->mlx, vars->coin);
			mlx_destroy_image(vars->mlx, vars->exit);
			mlx_clear_window(vars->mlx, vars->win);
			mlx_destroy_window(vars->mlx, vars->win);
			mlx_destroy_display(vars->mlx);
			free(vars->mlx);
			exit(write(1, "collectable not reachable!\n", 26));
		}
		i++;
	}
}

char	*helper3(char *map, int height)
{
	int		x;
	int		i;
	char	*tmp;

	tmp = (char *)ft_calloc(sizeof(char), (ft_strlen(map) - height + 1));
	x = 0;
	i = 0;
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
	return (tmp);
}

static void	struct_init(t_vars *vars, char *av, char *tmp, int *flag)
{
	vars->map = clone_map(av);
	calc_size(vars);
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, vars->map_width * TILE_SIZE,
			vars->map_height * TILE_SIZE, "So_Long");
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
	vars->img_ptr = mlx_xpm_file_to_image(vars->mlx, "./img/grass.xpm",
			&vars->img_width, &vars->img_height);
	vars->wall_ptr = mlx_xpm_file_to_image(vars->mlx, "./img/wall.xpm",
			&vars->img_width, &vars->img_height);
	vars->coin = mlx_xpm_file_to_image(vars->mlx, "./img/coin.xpm",
			&vars->img_width, &vars->img_height);
	vars->exit = mlx_xpm_file_to_image(vars->mlx, "./img/exit.xpm",
			&vars->img_width, &vars->img_height);
	flag = 0;
}

static void	helper2(t_vars *vars)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	if (!vars->map)
		return ;
	while (vars->map[x] != '\n')
		x++;
	while (vars->map_no_nl[i] != 'P')
		i++;
	vars->pos_i = i;
	vars->map_width = x;
	i = 0;
}

static	void	check_shit(t_vars *vars, char *tmp)
{
	int	flag_e;
	int	flag_p;
	int	i;

	i = 0;
	flag_e = 0;
	flag_p = 0;
	while (vars->map_no_nl[i] != '\0')
	{
		if (vars->map_no_nl[i] == 'P')
			flag_p++;
		if (vars->map_no_nl[i] == 'E')
			flag_e++;
		i++;
	}
	if (flag_e > 1 || flag_p > 1)
	{
		free(tmp);
		ft_putstr_fd("Duplicate player or exit!\n", 2);
		free_exit(vars);
	}
}

int	main(int ac, char **av)
{
	t_vars		vars;
	int			flag;
	char		*tmp;

	struct_init(&vars, av[1], tmp, &flag);
	tmp = restock_map(vars.map);
	helper2(&vars);
	check_borders(&vars, tmp);
	check_shit(&vars, tmp);
	if (ac != 2)
		return (ft_putstr_fd("Error! Wrong number of arguments!\n", 2));
	if (map_error(vars.map, &vars) == TRUE)
		return (ft_putstr_fd("Error! Unrecognized symbol in map\n", 2));
	if (vars.map != NULL)
		flood_fill(vars.map_no_nl, vars, vars.pos_i, &flag);
	check_collectables(vars.map_no_nl, &vars, tmp);
	if (flag <= 0)
		return (ft_putstr_fd("Error! No path to exit in selected map!\n", 2));
	mlx_hook(vars.win, 17, 0, &exit_hook, &vars);
	mlx_key_hook(vars.win, &key_hook, &vars);
	render_map(&vars);
	render_player(&vars, vars.map, "./img/chara.xpm");
	ft_printf("collectables on map: %d\n", vars.total_collectable);
	mlx_loop(vars.mlx);
	return (0);
}
