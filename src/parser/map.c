/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:47:09 by amolbert          #+#    #+#             */
/*   Updated: 2024/06/28 16:47:33 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	check_space(t_cub *cb, int start, int j, int len)
{
	if (cb->map.height_file - start < cb->map.height)
		if (cb->map.file[start - 1][j] == '0')
			return (1);
	if (cb->map.height_file - start < 0)
		if (cb->map.file[start + 1][j] == '0')
			return (1);
	if (j > 0)
		if (cb->map.file[start][j - 1] == '0')
			return (1);
	if (j < len - 1)
		if (cb->map.file[start][j + 1] == '0')
			return (1);
	return (0);
}

static void	copy_map(t_cub *cb, char **map, int start, int len)
{
	int			j;
	static int	i = 0;

	j = 0;
	while (cb->map.file[start][j])
	{
		if (cb->map.file[start][j] != '\n' && cb->map.file[start][j] != ' ')
			map[i][j] = cb->map.file[start][j];
		else if (cb->map.file[start][j] == ' ')
		{
			if (check_space(cb, start, j, len))
				map[i][j] = '1';
			else
				map[i][j] = ' ';
		}
		else
			map[i][j] = '\0';
		j++;
	}
	while (j < len)
	{
		map[i][j] = '\0';
		j++;
	}
	i++;
}

static char	**extract_map(t_cub *cb, int start)
{
	int		i;
	int		len;
	char	**map;

	i = 0;
	map = ft_calloc(sizeof(char *), (cb->map.height + 1));
	if (!map)
		return (NULL);
	len = find_max_len(cb->map.file, start, cb->map.height);
	while (i < cb->map.height)
	{
		map[i] = malloc(sizeof(char) * (len + 1));
		if (!map[i])
			error(cb, MALLOC_ERROR);
		map[i][len] = '\0';
		copy_map(cb, map, start, len);
		start++;
		i++;
	}
	return (map);
}

static int	save_height(t_cub *cb, int i, int height_file)
{
	char	**line;

	line = ft_split(cb->map.file[i], ' ');
	if (!line)
		error(cb, MALLOC_ERROR);
	if (!ft_strncmp(line[0], "1", 1))
	{
		cb->map.height = height_file - i;
		free_array(line);
		return (1);
	}
	free_array(line);
	return (0);
}

void	save_map(t_cub *cb, int height_file)
{
	int		i;

	i = 0;
	while (cb->map.file[i])
	{
		if (save_height(cb, i, height_file))
			break ;
		i++;
	}
	if (!cb->map.height)
		error(cb, HEIGHT_ERROR);
	cb->map.map = extract_map(cb, i);
	if (!cb->map.map)
		error(cb, MALLOC_ERROR);
}
