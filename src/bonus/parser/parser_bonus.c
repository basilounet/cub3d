/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:32:52 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/23 13:47:36 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	check_path2(t_cub *cb, char *str, char *id)
{
	int				i;
	mlx_texture_t	*tmp;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			str[i] = '\0';
		i++;
	}
	tmp = mlx_load_png(str);
	if (!tmp)
		return (1);
	mlx_delete_texture(tmp);
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

	tmp = ft_atoi(color);
	if (!ft_strncmp(id, "F", 2))
	{
		if (count == 1)
		{
			cb->map.floor_color = tmp;
		}
		else if (count == 2)
		{
			cb->map.floor_color = (cb->map.floor_color << 8) + tmp;
		}
		else
		{
			cb->map.floor_color = (cb->map.floor_color << 8) + tmp;
			cb->map.floor_color = (cb->map.floor_color << 8) + 255;
		}
	}
	else
	{
		if (count == 1)
			cb->map.ceiling_color = tmp;
		else if (count == 2)
			cb->map.ceiling_color = (cb->map.ceiling_color << 8) + tmp;
		else
		{
			cb->map.ceiling_color = (cb->map.ceiling_color << 8) + tmp;
			cb->map.ceiling_color = (cb->map.ceiling_color << 8) + 255;
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
				return (1);
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
	int		i;
	int		k;
	int		status;
	char	**line;

	i = 0;
	while (cb->map.file[i])
	{
		line = ft_split(cb->map.file[i], ' ');
		ft_printf("%s", cb->map.file[i]);
			///////////////////////////////////////////////////////
		if (!line)
			error(cb, MALLOC_ERROR);
		if (ft_maplen(line) > 2 && line[2][0] != '\n')
			error(cb, TOO_MANY_ARG_ON_LINE);
		if (!ft_strncmp(line[0], "1", 1))
		{
			free_array(line);
			break ;
		}
		k = 0;
		while (cb->map.param[k])
		{
			status = 0;
			if (k < 4)
			{
				if (!ft_strncmp(line[0], cb->map.param[k], 3))
				{
					if (!cb->map.par[k])
					{
						if (!check_path2(cb, line[1], cb->map.param[k]))
						{
							status = 1;
							cb->map.par[k] = 1;
							break ;
						}
					}
					free_array(line);
					error(cb, PATH_ERROR);
				}
			}
			else
			{
				if (!ft_strncmp(line[0], cb->map.param[k], 2))
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
		if (!status && ft_strncmp(line[0], "\n", 1))
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
		while (file[start][j])
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
			if (cb->map.file[start][j] != '\n' && cb->map.file[start][j] != ' ')
				map[i][j] = cb->map.file[start][j];
			else if (cb->map.file[start][j] == ' ')
				map[i][j] = '1';
			else
				map[i][j] = '\0';
			j++;
		}
		while (j < len + 1)
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
	int		i;
	int		j;
	int		height;
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
			break ;
		}
		free_array(line);
		i++;
	}
	if (!height)
		error(cb, HEIGHT_ERROR);
	map = extract_map(cb, i, height);
	if (!map)
		return (NULL);
	return (map);
}

void	check_blank_line(t_cub *cb)
{
	int	i;
	int	j;
	int	status;

	i = 0;
	while (cb->map.map[i])
	{
		j = 0;
		status = 0;
		while (cb->map.map[i][j])
		{
			if (cb->map.map[i][j] != '\0')
				status = 1;
			j++;
		}
		if (!status)
			error(cb, EMPTYLINE_ERROR);
		i++;
	}
}

int	ft_isplayer(int c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

void	check_char(t_cub *cb)
{
	int	i;
	int	j;
	int	status;

	i = 0;
	status = 0;
	while (cb->map.map[i])
	{
		j = 0;
		while (cb->map.map[i][j])
		{
			if (cb->map.map[i][j] != '0' && cb->map.map[i][j] != '1'
				&& !ft_isplayer(cb->map.map[i][j]))
				error(cb, BADCHAR_ERROR);
			if (ft_isplayer(cb->map.map[i][j]))
			{
				if (status)
					error(cb, PLAYER_ERROR);
				status = 1;
			}
			j++;
		}
		i++;
	}
	if (!status)
		error(cb, PLAYER_ERROR);
}

void	check_borders(t_cub *cb, int i, int j)
{
	int	len;
	int	height;

	len = ft_strlen(cb->map.map[i]);
	height = ft_maplen(cb->map.map);
	if (i == 0 || i == height - 1 || j == 0 || j == len - 1)
		error(cb, CLOSED_ERROR);
}

void	check_near_char(t_cub *cb, int i, int j)
{
	if (cb->map.map[i - 1][j] == '\0' || cb->map.map[i + 1][j] == '\0')
		error(cb, CLOSED_ERROR);
	if (cb->map.map[i][j - 1] == '\0' || cb->map.map[i + 1][j + 1] == '\0')
		error(cb, CLOSED_ERROR);
}

void	check_closed_map(t_cub *cb)
{
	int	i;
	int	j;

	i = 0;
	while (cb->map.map[i])
	{
		j = 0;
		while (cb->map.map[i][j])
		{
			if (cb->map.map[i][j] != '1')
			{
				check_borders(cb, i, j);
				check_near_char(cb, i, j);
			}
			j++;
		}
		i++;
	}
}

int	check_map(t_cub *cb)
{
	cb->map.height = ft_maplen(cb->map.file);
	cb->map.map = save_map(cb, cb->map.height);
	if (!cb->map.map)
		return (2);
	check_blank_line(cb);
	check_char(cb);
	check_closed_map(cb);
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
	cb->map.param = ft_calloc(sizeof(char *), 7);
	cb->map.param[0] = ft_strdup("NO");
	cb->map.param[1] = ft_strdup("SO");
	cb->map.param[2] = ft_strdup("EA");
	cb->map.param[3] = ft_strdup("WE");
	cb->map.param[4] = ft_strdup("F");
	cb->map.param[5] = ft_strdup("C");
	if (!cb->map.param[0] || !cb->map.param[1] || !cb->map.param[2]
		|| !cb->map.param[3] || !cb->map.param[4] || !cb->map.param[5])
		error(cb, MALLOC_ERROR);
	cb->map.par = ft_calloc(sizeof(int), 7);
	if (!cb->map.par)
		error(cb, MALLOC_ERROR);
}

void	parse(t_cub *cb, char *arg)
{
	char	*name;
	int		fd;

	ft_memset(cb, 0, sizeof(t_cub));
	fd = open(arg, O_RDONLY);
	if (fd < 0 || fd > 1023)
		error(cb, NO_FILE_ERROR);
	close(fd);
	name = strrchr(arg, '.');
	if (ft_strncmp(name, ".cub", 5))
		error(cb, NAME_ERROR);
	cb->map.file = ft_slurp(arg);
	if (!cb->map.file)
		error(cb, MALLOC_ERROR);
	set_param(cb);
	check_file(cb);
	// cb->map.width = ft_strlen(cb->map.map[0]);
	// cb->map.height = ft_maplen(cb->map.map);
	ft_print_map(cb->map.map, 1);
}
