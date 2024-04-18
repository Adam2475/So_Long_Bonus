/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adapassa <adapassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:10:13 by adapassa          #+#    #+#             */
/*   Updated: 2024/04/18 14:51:20 by adapassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static char	*ft_strjoin_gnl2(char *s1, char const *s2)
{
	char	*s3;
	int		i;
	int		j;

	i = 0;
	j = -1;
	s3 = (char *)ft_custom_function(sizeof(char),
			((long)ft_custom_function(0, 0, (char *)s1, 0)
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

char	*clone_map(char *map)
{
	char	*tmp;
	char	*holder;
	int		fd;

	holder = NULL;
	fd = open(map, O_RDONLY);
	if (fd < 0)
		exit(write(1, "error, map not found!\n", 22));
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
	int	i;

	i = 0;
	if (!map)
		return (TRUE);
	while (map[i] != '\0')
	{
		if ((map[i] != '0') && (map[i] != '1') && (map[i] != 'P')
			&& (map[i] != 'C') && (map[i] != '\n') && (map[i] != 'E'))
			return (TRUE);
		if (map[i] == 'C')
			vars->total_collectable++;
		i++;
	}
	return (FALSE);
}

bool	helper1(t_vars *vars, int i, int j)
{
	while (i < (j - vars->map_width))
	{
		if (i % vars->map_width == 0)
		{
			if (vars->map_no_nl[i] != '1')
				return (true);
		}
		else if ((i + 1) % vars->map_width == 0)
		{
			if (vars->map_no_nl[i] != '1')
				return (true);
		}
		i++;
	}
	while (i < j)
	{
		if (vars->map_no_nl[i] != '1')
			return (true);
		i++;
	}
	return (false);
}
