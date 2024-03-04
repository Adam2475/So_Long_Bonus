#include "../so_long.h"

static char	*ft_strjoin_gnl2(char *s1, char const *s2)
{
	char	*s3;
	int		i;
	int		j;

	i = 0;
	j = -1;
	s3 = (char *)ft_custom_function(sizeof(char), ((long)ft_custom_function(0, 0, (char *)s1, 0)
				+ (long)ft_custom_function(0, 0, (char *)s2, 0) + 1), NULL, 1);
	if (!s3)
		return (0);
	if (s1)
	{
		while (s1[i] != '\0')
		{
			s3[i] = s1[i];
			i++;
		}
		free(s1);
	}
	while (s2[++j] != '\0')
		s3[i + j] = s2[j];
	s3[i + j] = '\0';
	return (s3);
}

char *clone_map(char *map)
{
	char	*tmp;
	char	*holder;
	int		fd;

	holder = NULL;
	fd = open("./map.ber", O_RDONLY);
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		holder = ft_strjoin_gnl2(holder, tmp);
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

bool	check_borders(t_vars vars)
{
	int i = 0;
	int j = 0;
	int y = 0;
	//char *tmp;

	while (vars.map[y] != '\0')
	{
		if (vars.map[y] == '\n')
			j++;
		y++;
	}

	if (!vars.map_no_nl)
		return (true);
	//tmp = restock_map(vars.map);
	vars.map_height = j;

	while (vars.map_no_nl[i] && vars.map_no_nl[i] != '\0')
	{
		while (i < vars.map_width)
		{
			if (vars.map_no_nl[i] != '1')
				return (true);
			i++;
		}
		if (i % vars.map_width == 0)
		{
			if (vars.map_no_nl[i] != '1')
				return (true);
			if (vars.map_no_nl[i - 1] != '1')
				return (true);
			if (vars.map_no_nl[i + (vars.map_width - 1)] != '1')
				return (true);
		}
		i++;
		if (i >= ((y - j - vars.map_width)))
		{
			while (vars.map_no_nl[i] && vars.map_no_nl[i + 1] != '\0')
			{
				//if (!vars.map_no_nl[i] || i >= ft_strlen(vars.map_no_nl))
				//	break ;
				if (vars.map_no_nl[i] != '1')
					return (true);
				i++;
			}
			return (false);
		}
	}
	return (false);
}

void flood_fill(char *map, t_vars vars, int position, int *flag)
{
	if (map[position + 1] == 'E' || map[position - 1] == 'E'
			|| map[position - vars.map_width] == 'E' || map[position + vars.map_width] == 'E')
		*flag = 1;
	if (map[position + 1] == '0'  || map[position + 1] == 'C')
	{
		map[position] = 'F';
		flood_fill(map, vars, position + 1, flag);
	}
	if (map[position + vars.map_width] == '0' || map[position + vars.map_width] == 'C')
	{
		map[position] = 'F';
		flood_fill(map, vars, position + vars.map_width, flag);
	}
	if (map[position - 1] == '0' || map[position - 1] == 'C')
	{
		map[position] = 'F';
		flood_fill(map, vars, position - 1, flag);
	}
	if (map[position - vars.map_width] == '0' || map[position - vars.map_width] == 'C')
	{
		map[position] = 'F';
		flood_fill(map, vars, position - vars.map_width, flag);
	}
}



