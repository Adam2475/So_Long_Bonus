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
