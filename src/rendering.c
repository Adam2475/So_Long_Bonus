/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:34:18 by adapassa          #+#    #+#             */
/*   Updated: 2024/03/07 16:40:26 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	helper(t_vars *vars, int *i)
{
	while (i[3] <= i[0])
	{
		if (vars->map[i[4]] == '0' || vars->map[i[4]] == 'P')
			mlx_put_image_to_window(vars->mlx, vars->win,
				vars->img_ptr, i[3] * 32, i[2] * 32);
		else if (vars->map[i[4]] == '1')
			mlx_put_image_to_window(vars->mlx, vars->win,
				vars->wall_ptr, i[3] * 32, i[2] * 32);
		else if (vars->map[i[4]] == 'C')
			mlx_put_image_to_window(vars->mlx, vars->win,
				vars->coin, i[3] * 32, i[2] * 32);
		else if (vars->map[i[4]] == 'E')
			mlx_put_image_to_window(vars->mlx, vars->win,
				vars->exit, i[3] * 32, i[2] * 32);
		i[3]++;
		i[4]++;
	}
}

void	render_map(t_vars *vars)
{
	int	i[5];

	i[0] = 0;
	i[1] = 1;
	i[4] = 0;
	i[2] = 0;
	i[3] = 0;
	while (vars->map[i[0]] != '\0')
	{
		if (vars->map[i[0]] == '\n')
			i[1]++;
		i[0]++;
	}
	i[0] = i[0] / i[1];
	vars->map_width = i[0];
	vars->map_height = i[1];
	while (i[2] < i[1])
	{
		helper(vars, i);
		i[3] = 0;
		i[2]++;
	}
}

void	*render_player(t_vars *vars, char *map, char *path)
{
	int	i;
	int	x;
	int	z;

	x = 0;
	z = 0;
	i = 0;
	while (map[x] != '\n')
		x++;
	while (map[i] != 'P')
	{
		if (map[i] == '\n')
			z++;
		i++;
	}
	vars->player_i = vars->pos_i + 1;
	vars->pos_y = z;
	vars->pos_x = (i % x) - vars->pos_y;
	vars->player_image = mlx_xpm_file_to_image(vars->mlx, path,
			&vars->img_width, &vars->img_height);
	mlx_put_image_to_window(vars->mlx, vars->win,
		vars->player_image, vars->pos_x * TILE_SIZE, vars->pos_y * TILE_SIZE);
	return (NULL);
}

char	*restock_map(char *map)
{
	int		i;
	char	*tmp;
	int		j;
	int		height;

	i = 0;
	j = 0;
	height = 0;
	while (map[i] != '\0')
	{
		if (map[i] == '\n')
			height++;
		i++;
	}
	i = 0;
	tmp = helper3(map, height);
	i = i - height;
	tmp[i] = '\0';
	return (tmp);
}
