/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:47:09 by amolbert          #+#    #+#             */
/*   Updated: 2024/07/31 15:45:39 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

static int	check_space(t_cub *cb, int start, int j, int len)
{
	if (start > cb->map.height_file - cb->map.height)
		if (!is_impediment(cb->map.file[start - 1][j]))
			return (1);
	if (start < cb->map.height_file - 1)
		if (!is_impediment(cb->map.file[start + 1][j]))
			return (1);
	if (j > 0)
		if (!is_impediment(cb->map.file[start][j - 1]))
			return (1);
	if (j < len - 1)
		if (!is_impediment(cb->map.file[start][j + 1]))
			return (1);
	return (0);
}

static void	copy_map(t_cub *cb, int start, int len)
{
	int			j;
	static int	i = 0;

	j = 0;
	while (cb->map.file[start][j])
	{
		if (cb->map.file[start][j] != '\n' && cb->map.file[start][j] != ' ')
		{
			cb->map.map[i][j] = cb->map.file[start][j];
			if (cb->map.file[start][j] == 'I' || cb->map.file[start][j] == 'M')
				cb->nb_of_entities++;
		}
		else if (cb->map.file[start][j] == ' ')
		{
			if (check_space(cb, start, j, len))
				cb->map.map[i][j] = '1';
			else
				cb->map.map[i][j] = ' ';
		}
		else
			cb->map.map[i][j] = '\0';
		j++;
	}
	fill_map(cb, i, j, len);
	i++;
}

void	extract_map(t_cub *cb, int start)
{
	int		i;
	int		len;

	i = 0;
	cb->map.map = ft_calloc(sizeof(char *), (cb->map.height + 1));
	if (!cb->map.map)
		error(cb, MALLOC_ERROR);
	len = find_max_len(cb->map.file, start, cb->map.height);
	while (i < cb->map.height)
	{
		cb->map.map[i] = malloc(sizeof(char) * (len + 1));
		if (!cb->map.map[i])
			error(cb, MALLOC_ERROR);
		cb->map.map[i][len] = '\0';
		copy_map(cb, start, len);
		start++;
		i++;
	}
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
	extract_map(cb, i);
}
