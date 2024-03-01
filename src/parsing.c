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

	//ft_printf("%s\n", map);

	while (vars.map[y] != '\0')
	{
		if (vars.map[y] == '\n')
			j++;
		y++;
	}

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

bool flood_fill(char *map, t_vars vars, int position, int *flag)
{
	if (map[position + 1] == 'E' || map[position - 1] == 'E'
			|| map[position - vars.map_width] == 'E' || map[position + vars.map_width] == 'E')
		*flag = 1;
	if (map[position + 1] == '0'  || map[position + 1] == 'C')
	{
		map[position] = 'F';
		//ft_printf("right %d\n", i);
		flood_fill(map, vars, position + 1, flag);
	}
	if (map[position + vars.map_width] == '0' || map[position + vars.map_width] == 'C')
	{
		map[position] = 'F';
		//ft_printf("down %d\n", i);
		flood_fill(map, vars, position + vars.map_width, flag);
	}
	if (map[position - 1] == '0' || map[position - 1] == 'C')
	{
		map[position] = 'F';
		//ft_printf("left %d\n", i);
		flood_fill(map, vars, position - 1, flag);
	}
	if (map[position - vars.map_width] == '0' || map[position - vars.map_width] == 'C')
	{
		map[position] = 'F';
		//ft_printf("up %d\n", i);
		flood_fill(map, vars, position - vars.map_width, flag);
	}
}



