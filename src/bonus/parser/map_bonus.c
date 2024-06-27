/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:47:09 by amolbert          #+#    #+#             */
/*   Updated: 2024/06/27 13:11:10 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

static void	copy_map(t_cub *cb, char **map, int start, int i)
{
	int	j;

	j = 0;
	while (cb->map.file[start][j])
	{
		if (cb->map.file[start][j] != '\n' && cb->map.file[start][j] != ' ')
			map[i][j] = cb->map.file[start][j];
		else if (cb->map.file[start][j] == ' ')
			map[i][j] = '1';
		else
			map[i][j] = '\0';
		j++;
	}
	while (map[i][j])
	{
		map[i][j] = '\0';
		j++;
	}
}

static char	**extract_map(t_cub *cb, int start, int height)
{
	int		i;
	int		len;
	char	**map;

	i = 0;
	map = ft_calloc(sizeof(char *), (height + 1));
	if (!map)
		return (NULL);
	len = find_max_len(cb->map.file, start, height);
	while (i < height)
	{
		map[i] = malloc(sizeof(char) * (len + 1));
		if (!map[i])
			error(cb, MALLOC_ERROR);
		map[i][len] = '\0';
		copy_map(cb, map, start, i);
		start++;
		i++;
	}
	return (map);
}

static int	save_height(t_cub *cb, int i, int height_file, int *height)
{
	char	**line;

	line = ft_split(cb->map.file[i], ' ');
	if (!line)
		error(cb, MALLOC_ERROR);
	if (!ft_strncmp(line[0], "1", 1))
	{
		*height = height_file - i;
		free_array(line);
		return (1);
	}
	free_array(line);
	return (0);
}

void	save_map(t_cub *cb, int height_file)
{
	int		i;
	int		height;

	height = 0;
	i = 0;
	while (cb->map.file[i])
	{
		if (save_height(cb, i, height_file, &height))
			break ;
		i++;
	}
	if (!height)
		error(cb, HEIGHT_ERROR);
	cb->map.map = extract_map(cb, i, height);
	if (!cb->map.map)
		error(cb, MALLOC_ERROR);
}
