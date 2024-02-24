#include "../so_long.h"

char *clone_map(char *map)
{
	char *tmp;
	char *holder;
	int fd;

	holder = NULL;
	fd = open(map, O_RDONLY);
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		holder = ft_strjoin_gnl(holder, tmp);
		free(tmp);
	}
	close(fd);
	return (holder);
}

int	map_error(char *map, t_vars *vars)
{
	int i;

	i = 0;
	while (map[i] != '\0')
	{
		//ft_printf("%c\n", map[i]);
		if ((map[i] != '0') && (map[i] != '1') && (map[i] != 'P') && (map[i] != 'C') && (map[i] != '\n') && (map[i] != 'E'))
			return (TRUE);
		if (map[i] == 'C')
			vars->total_collectable++;
		i++;
	}
	return (FALSE);
}

bool	check_borders(char *map, t_vars vars)
{
	int i = 0;
	int j = 0;
	int y = 0;

	while (vars.map[y] != '\0')
	{
		if (vars.map[y] == '\n')
			j++;
		y++;
	}

	ft_printf("%d\n", y);
	ft_printf("%d\n", ft_strlen(vars.map_no_nl));
	vars.map_height = j;

	while (map[i] != '\0')
	{
		while (i < vars.map_width)
		{
			if (map[i] != '1')
				return (true);
			i++;
		}
		if (i % vars.map_width == 0)
		{
			if (map[i] != '1')
				return (true);
			if (map[i - 1] != '1')
				return (true);
			if (map[i + (vars.map_width - 1)] != '1')
				return (true);
		}
		i++;
		if (i >= ((y - j - vars.map_width)))
		{
			while (map[i] != '\0')
			{
				if (map[i] != '1')
					return (true);
				i++;
			}
		}
	}
	return (false);
}

bool flood_fill(char *map, t_vars vars, int position)
{
	if (map[vars.pos_i + 1] == '0'  || map[vars.pos_i + 1] == 'C')
	{
		map[vars.pos_i] = 'F';
		vars.pos_i = vars.pos_i + 1;
		flood_fill(map, vars, vars.pos_i + 1);
	}
	if (map[vars.pos_i - 1] == '0' || map[vars.pos_i - 1] == 'C')
	{
		map[vars.pos_i] = 'F';
		vars.pos_i = vars.pos_i - vars.map_width;
		flood_fill(map, vars, vars.pos_i - 1);
	}
	if (map[vars.pos_i - vars.map_width] == '0' || map[vars.pos_i - vars.map_width] == 'C')
	{
		map[vars.pos_i] = 'F';
		vars.pos_i = vars.pos_i + 1;
		flood_fill(map, vars, vars.pos_i - vars.map_width);
	}
	if (map[vars.pos_i + vars.map_width] == '0' || map[vars.pos_i + vars.map_width] == 'C')
	{
		map[vars.pos_i] = 'F';
		vars.pos_i = vars.pos_i + vars.map_width;
		flood_fill(map, vars, vars.pos_i + vars.map_width);
	}
}



