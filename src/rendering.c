#include "../so_long.h"
#include "../mlx_linux/mlx.h"

void	render_map(t_vars *vars)
{
	int i;
	int j;
	int z;
	int x;

	i = 0;
	j = 1;
	int p = 0;

	while (vars->map[i] != '\0')
	{
		if (vars->map[i] == '\n')
			j++;
		i++;
	}
	i = i / j;
	x = 0;
	z = 0;
	vars->map_width = i;
	vars->map_height = j;
	while (z < j)
	{
		while (x <= i)
		{
			if (vars->map[p] == '0' || vars->map[p] == 'P')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->img_ptr, x * 32, z * 32);
			else if (vars->map[p] == '1')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->wall_ptr, x * 32, z * 32);
			else if (vars->map[p] == 'C')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->coin, x * 32, z * 32);
			else if (vars->map[p] == 'E')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->exit, x * 32, z * 32);
			x++;
			p++;
		}
		x = 0;
		z++;
	}
	return ;
}

void	*render_player(t_vars *vars, char *map, char *path)
{
	int i;
	int	x;
	int z;

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
	vars->player_image = mlx_xpm_file_to_image(vars->mlx, path, &vars->img_width, &vars->img_height);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->player_image, vars->pos_x * TILE_SIZE,  vars->pos_y * TILE_SIZE);
	return (NULL);
}
