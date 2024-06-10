/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:32:52 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/10 15:28:04 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	check_path2(char *str)
{
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strchr(str, '.');
	path = strdup(tmp);
	if (!path)
		return (1);
	while (path[i])
	{
		if (path[i] == '\n')
			path[i] = path[i + 1];
		i++;
	}
	if (!mlx_load_png(path))
	{
		free(path);
		printf("pas ok\n");
		return (1);
	}
	printf("ok\n");
	free(path);
	return (0);
}

int	check_path(t_cub *cb, char *id, char *b_id, char *ba_id, char *bad_id)
{
	static int	i = 0;
	int			j;

	while (cb->map.map[i])
	{
		j = 0;
		while (cb->map.map[i][j])
		{
			if (!ft_strncmp(cb->map.map[i] + j, id, 2))
			{
				if (!check_path2(cb->map.map[i] + j))
				{
					i++;
					return (0);
				}
				else
					return (1);
			}
			if (!ft_strncmp(cb->map.map[i] + j, b_id, 2)
				|| !ft_strncmp(cb->map.map[i] + j, ba_id, 2)
				|| !ft_strncmp(cb->map.map[i] + j, bad_id, 2))
				return (1);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_file(t_cub *cb)
{
	if (check_path(cb, "NO", "SO", "WE", "EA"))
		return (1);
	if (check_path(cb, "SO", "WE", "EA", "NO"))
		return (1);
	if (check_path(cb, "WE", "EA", "NO", "SO"))
		return (1);
	if (check_path(cb, "EA", "NO", "SO", "WE"))
		return (1);
	/*if (check_color(cb))
		return (1);
	if (check_map(cb))
		return (1);*/
	return (0);
}

void	parse(t_cub *cb)
{
	ft_memset(cb, 0, sizeof(t_cub));
	cb->map.map = ft_slurp("maps/subject.cub");
	if (!cb->map.map)
		error(cb, MALLOC_ERROR);
	if (check_file(cb))
		error(cb, PATH_ERROR);
	cb->map.width = ft_strlen(cb->map.map[0]);
	cb->map.height = ft_maplen(cb->map.map);
	ft_print_map(cb->map.map);
}
