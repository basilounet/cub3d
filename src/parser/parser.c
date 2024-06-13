/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:32:52 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/13 13:36:28 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	check_path2(t_cub *cb, char *str, char *id)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			str[i] = '\0';
		i++;
	}
	if (!mlx_load_png(str))
		return (1);
	if (!ft_strncmp(id, "NO", 3))
		cb->map.north_texture = mlx_load_png(str);
	if (!ft_strncmp(id, "SO", 3))
		cb->map.south_texture = mlx_load_png(str);
	if (!ft_strncmp(id, "WE", 3))
		cb->map.west_texture = mlx_load_png(str);
	if (!ft_strncmp(id, "EA", 3))
		cb->map.east_texture = mlx_load_png(str);
	return (0);
}

int	check_path(t_cub *cb, char *id)
{
	int	i;
	int j;
	int	status;
	char	**line;

	i = 0;
	status = 0;
	while (cb->map.file[i])
	{
		j = 0;
		line = ft_split(cb->map.file[i], ' ');
		if (!line)
			error(cb, MALLOC_ERROR);
		while (line[j])
		{
			if (!ft_strncmp(line[j], id, 3))
			{
				if (!check_path2(cb, line[j + 1], id))
				{
					if (status)
						return (1);
					status = 1;
					break ;
				}
				else
					return (1);
			}
			j++;
		}
		free_array(line);
		i++;
	}
	if (status)
		return (0);
	return (1);
}

int	chech_size_arg(char *arg)
{
	int	i;
	int	s;

	i = 0;
	s = 0;
	while (arg[i])
	{
		if (s * 10 + (arg[i] - '0') > 255)
			return (1);
		s = s * 10 + (arg[i] - '0');
		i++;
	}
	return (0);
}

void	save_color(t_cub *cb, char *color, int count, char *id)
{
	int	tmp;
	int	len;

	tmp = ft_atoi(color);
	len = ft_strlen(color);
	if (!ft_strncmp(id, "F", 2))
	{
		if (count == 1)
		{
			cb->map.floor_color = tmp;
		}
		else if (count == 2)
		{
			cb->map.floor_color = cb->map.floor_color * ft_power(10, len) + tmp;
		}
		else
		{
			cb->map.floor_color = cb->map.floor_color * ft_power(10, len) + tmp;
			cb->map.floor_color = cb->map.floor_color * ft_power(10, 3) + 255;
		}
	}
	else
	{
		if (count == 1)
			cb->map.ceiling_color = tmp;
		else if (count == 2)
			cb->map.ceiling_color = cb->map.ceiling_color * ft_power(10, len) + tmp;
		else
		{
			cb->map.ceiling_color = cb->map.ceiling_color * ft_power(10, len) + tmp;
			cb->map.ceiling_color = cb->map.ceiling_color * ft_power(10, 3) + 255;
		}
	}
}

int	check_color2(t_cub *cb, char **line, char *id)
{
	int		i;
	int		j;
	int		k;
	int		count;
	char	**color;

	i = 1;
	count = 0;
	while (line[i])
	{
		j = 0;
		color = ft_split(line[i], ',');
		if (!color)
			return (2);
		while (color[j])
		{
			k = 0;
			while (color[j][k])
			{
				if (color[j][k] == '\n')
					color[j][k] = '\0';
				k++;
			}
			k = 0;
			if (color[j] == NULL || color[j][k] == '\0')
				return (1);
			while (ft_isdigit(color[j][k]))
				k++;
			if (color[j][k])
				return(1);
			if (chech_size_arg(color[j]))
				return (1);
			count++;
			save_color(cb, color[j], count, id);
			j++;
		}
		free_array(color);
		i++;
	}
	if (count != 3)
		return (1);
	return (0);
}

int	check_color(t_cub *cb, char *id)
{
	int	i;
	int j;
	int	status;
	char	**line;

	i = 0;
	status = 0;
	while (cb->map.file[i])
	{
		j = 0;
		line = ft_split(cb->map.file[i], ' ');
		if (!line)
			error(cb, MALLOC_ERROR);
		while (line[j])
		{
			if (!ft_strncmp(line[j], id, 2))
			{
				if (!check_color2(cb, line, id))
				{
					if (status)
						return (1);
					status = 1;
					break ;
				}
				else
					return (1);
			}
			j++;
		}
		free_array(line);
		i++;
	}
	if (status)
		return (0);
	return (1);
}

int	find_max_len(char **map)
{
	int	len;
	int	i;
	int	j;

	i = 0;
	len = 0;
	while (map[i])
	{
		j = 0;
		while(map[i][j])
		{
			j++;
		}
		if (map[i][j - 1] == '\n')
			j--;
		if (j > len)
			len = j;
		i++;
	}
	return (len);
}

char	**extract_map(t_cub *cb, int start, int height)
{
	int		i;
	int		j;
	int		len;
	char	**map;

	i = 0;
	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	len = find_max_len(cb->map.map);
	while (i < height)
	{
		j = 0;
		map[i] = malloc(sizeof(char) * (len + 1));
		while (cb->map.file[start][j])
		{
			j++;
		}
		i++;
	}
	return (map);
}

char	**save_map(t_cub *cb, int height_file)
{
	int	j;
	int	height;
	char	**map;

	height = 0;
	while (height_file < 0)
	{
		j = 0;
		while (cb->map.file[height_file][j] == ' ')
			j++;
		if (cb->map.file[height_file][j] != '\n')
			height++;
		else if (cb->map.file[height_file][j] != '\n' && height)
			break ;
		height_file--;
	}
	map = extract_map(cb, height_file, height);
	if (!map)
		return (NULL);
	return (map);
}

int	check_map(t_cub *cb)
{
	(void)cb;
	int	height_file;

	height_file = ft_maplen(cb->map.file);
	cb->map.map = save_map(cb, height_file);
	if (!cb->map.map)
		return (2);
	
	return (0);
}

void	check_file(t_cub *cb)
{
	if (check_path(cb, "NO"))
		error(cb, PATH_ERROR);
	if (check_path(cb, "SO"))
		error(cb, PATH_ERROR);
	if (check_path(cb, "WE"))
		error(cb, PATH_ERROR);
	if (check_path(cb, "EA"))
		error(cb, PATH_ERROR);
	if (check_color(cb, "F"))
		error(cb, COLOR_ERROR);
	if (check_color(cb, "C"))
		error(cb, COLOR_ERROR);
	/*if (check_map(cb))
		return (1);*/
}

void	parse(t_cub *cb, char *arg)
{
	char	*name;

	name = strrchr(arg, '.');
	if (ft_strncmp(name, ".cub", 5))
		error(cb, NAME_ERROR);
	ft_memset(cb, 0, sizeof(t_cub));
	cb->map.file = ft_slurp(arg);
	if (!cb->map.file)
		error(cb, MALLOC_ERROR);
	check_file(cb);
	//cb->map.width = ft_strlen(cb->map.map[0]);
	//cb->map.height = ft_maplen(cb->map.map);
	ft_print_map(cb->map.file);
}
