#include "../so_long.h"

char *clone_map(char *map)
{
	char *tmp;
	char *holder;
	//char map[][];
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

int	map_error(char *map)
{
	int i;

	i = 0;
	while (map[i] != '\0')
	{
		if (map[i] != '0' || map[i] != '1' || map[i] != 'P')
			return (TRUE);
		i++;
	}
	return (FALSE);
}
