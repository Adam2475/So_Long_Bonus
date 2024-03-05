#include "../so_long.h"
#include "../mlx_linux/mlx.h"

void	render_map(t_vars *vars, char *map, char *relative_path, char *wall_path, char *coin_ptr, char *exit_ptr)
{
	int i;
	int j;
	int z;
	int x;
	void *img_ptr;
	void *wall_ptr;
	int img_width = 32;
	int img_height = 32;
	void *coin;
	void *exit;

	i = 0;
	j = 1;
	int p = 0;
	img_ptr = mlx_xpm_file_to_image(vars->mlx, relative_path, &img_width, &img_height);
	wall_ptr = mlx_xpm_file_to_image(vars->mlx, wall_path, &img_width, &img_height);
	coin = mlx_xpm_file_to_image(vars->mlx, coin_ptr, &img_width, &img_height);
	exit = mlx_xpm_file_to_image(vars->mlx, exit_ptr, &img_width, &img_height);
	while (map[i] != '\0')
	{
		if (map[i] == '\n')
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
			if (map[p] == '0' || map[p] == 'P')
				mlx_put_image_to_window(vars->mlx, vars->win, img_ptr, x * 32, z * 32);
			else if (map[p] == '1')
				mlx_put_image_to_window(vars->mlx, vars->win, wall_ptr, x * 32, z * 32);
			else if (map[p] == 'C')
				mlx_put_image_to_window(vars->mlx, vars->win, coin, x * 32, z * 32);
			else if (map[p] == 'E')
				mlx_put_image_to_window(vars->mlx, vars->win, exit, x * 32, z * 32);
			x++;
			p++;
		}
		x = 0;
		z++;		
	}
	mlx_destroy_image(vars->mlx, img_ptr);
	mlx_destroy_image(vars->mlx, wall_ptr);
	mlx_destroy_image(vars->mlx, coin);
	mlx_destroy_image(vars->mlx, exit);
	return ;
}

void	*render_player(t_vars *vars, char *map, char *path)
{
	int i;
	int	x;
	int z;
	int height;
	int width;

	x = 0;
	z = 0;
	i = 0;
	while (map[x] != '\n')
	{
		x++;
	}
	while (map[i] != 'P')
	{
		if (map[i] == '\n')
			z++;
		i++;
	}
	vars->player_i = vars->pos_i + 1;
	vars->pos_y = z;
	vars->pos_x = (i % x) - vars->pos_y;
	vars->player_image = mlx_xpm_file_to_image(vars->mlx, path, &height, &width);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->player_image, vars->pos_x * TILE_SIZE,  vars->pos_y * TILE_SIZE);
	return (NULL);
}
