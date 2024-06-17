/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:32:52 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/17 17:21:43 by amolbert         ###   ########.fr       */
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

void	param_full(t_cub *cb)
{
	if (!cb->map.floor_color)
		error(cb, MISSING_ERROR);
	if (!cb->map.ceiling_color)
		error(cb, MISSING_ERROR);
	if (!cb->map.north_texture)
		error(cb, MISSING_ERROR);
	if (!cb->map.west_texture)
		error(cb, MISSING_ERROR);
	if (!cb->map.south_texture)
		error(cb, MISSING_ERROR);
	if (!cb->map.east_texture)
		error(cb, MISSING_ERROR);
}

void	check_param(t_cub *cb)
{
	int	i;
	int j;
	int	k;
	int	status;
	char	**line;

	i = 0;
	while (cb->map.file[i])
	{
		j = 0;
		line = ft_split(cb->map.file[i], ' ');
		if (!line)
			error(cb, MALLOC_ERROR);
		if (j > 1)
			error(cb, PARAM_ERROR);
		if (!ft_strncmp(line[j], "1", 1))
		{
			free_array(line);
			break;
		}
		k = 0;
		while (cb->map.param[k])
		{
			status = 0;
			if (k < 4)
			{
				if (!ft_strncmp(line[j], cb->map.param[k], 3))
				{
					if (!cb->map.par[k])
					{
						if (!check_path2(cb, line[j + 1], cb->map.param[k]))
						{
							status = 1;
							cb->map.par[k] = 1;
							break ;
						}
					}
					error(cb, PATH_ERROR);
				}
			}
			else
			{
				if (!ft_strncmp(line[j], cb->map.param[k], 2))
				{
					if (!cb->map.par[k])
					{
						if (!check_color2(cb, line, cb->map.param[k]))
						{
							status = 1;
							cb->map.par[k] = 1;
							break ;
						}
					}
					error(cb, COLOR_ERROR);
				}
			}
			k++;
		}
		if (!status && ft_strncmp(line[j], "\n", 1))
			error(cb, PARAM_ERROR);
		free_array(line);
		i++;
	}
	param_full(cb);
}

int	find_max_len(char **file, int start, int height)
{
	int	len;
	int	i;
	int	j;

	i = 0;
	len = 0;
	while (i < height)
	{
		j = 0;
		while(file[start][j])
			j++;
		if (file[start][j - 1] == '\n')
			j--;
		if (j > len)
			len = j;
		start++;
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
	map[height] = NULL;
	len = find_max_len(cb->map.file, start, height);
	while (i < height)
	{
		j = 0;
		map[i] = malloc(sizeof(char) * (len + 1));
		while (cb->map.file[start][j])
		{
			if (cb->map.file[start][j] != '\n')
				map[i][j] = cb->map.file[start][j];
			else
				map[i][j] = '\0';
			j++;
		}
		while(j < len + 1)
		{
			map[i][j] = '\0';
			j++;
		}
		start++;
		i++;
	}
	return (map);
}

char	**save_map(t_cub *cb, int height_file)
{
	int	i;
	int	j;
	int	height;
	char	**map;
	char	**line;

	height = 0;
	i = 0;
	while (cb->map.file[i])
	{
		j = 0;
		line = ft_split(cb->map.file[i], ' ');
		if (!line)
			error(cb, MALLOC_ERROR);
		if (j > 1)
			error(cb, PARAM_ERROR);
		if (!ft_strncmp(line[j], "1", 1))
		{
			height = height_file - i;
			free_array(line);
			break;
		}
		free_array(line);
		i++;
	}
	/*
	while (height_file > 0)
	{
		j = 0;
		while (cb->map.file[height_file - 1][j] == ' ')
			j++;
		if (cb->map.file[height_file - 1][j] != '\n' && cb->map.file[height_file - 1][j] != '\0')
			height++;
		if ((cb->map.file[height_file - 1][j] == '\n' || cb->map.file[height_file - 1][j] == '\0') && height)
			break ;
		height_file--;
	}*/
	if (!height)
		error(cb, HEIGHT_ERROR);
	map = extract_map(cb, i, height);
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
	check_param(cb);
	if (check_map(cb))
		error(cb, HEIGHT_ERROR);
}

void	set_param(t_cub *cb)
{
	cb->map.param = malloc(sizeof(char *) * 7);
	cb->map.param[6] = NULL;
	if (!cb->map.param)
		error(cb, MALLOC_ERROR);
	cb->map.param[0] = ft_strdup("NO");
	if (!cb->map.param[0])
		error(cb, MALLOC_ERROR);
	cb->map.param[1] = ft_strdup("SO");
	if (!cb->map.param[1])
		error(cb, MALLOC_ERROR);
	cb->map.param[2] = ft_strdup("EA");
	if (!cb->map.param[2])
		error(cb, MALLOC_ERROR);
	cb->map.param[3] = ft_strdup("WE");
	if (!cb->map.param[3])
		error(cb, MALLOC_ERROR);
	cb->map.param[4] = ft_strdup("F");
	if (!cb->map.param[4])
		error(cb, MALLOC_ERROR);
	cb->map.param[5] = ft_strdup("C");
	if (!cb->map.param[5])
		error(cb, MALLOC_ERROR);
	cb->map.par = ft_calloc(sizeof(int), 7);
	if (!cb->map.par)
		error(cb, MALLOC_ERROR);
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
	set_param(cb);
	check_file(cb);
	//cb->map.width = ft_strlen(cb->map.map[0]);
	//cb->map.height = ft_maplen(cb->map.map);
	ft_print_map(cb->map.map);
}
