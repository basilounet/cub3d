/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_param_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 08:41:48 by amolbert          #+#    #+#             */
/*   Updated: 2024/07/31 08:55:55 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

static int	check_path(t_cub *cb, char *str, char *id)
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

static int	check_param_color(t_cub *cb, char **line, int *status, int k)
{
	int	err;

	err = 0;
	if (!ft_strncmp(line[0], cb->map.param[k], 2))
	{
		if (!cb->map.par[k])
		{
			err = check_color(cb, line, cb->map.param[k]);
			if (err == 2)
			{
				free_array(line);
				error(cb, MALLOC_ERROR);
			}
			if (!err)
			{
				*status = 1;
				cb->map.par[k] = 1;
				return (1);
			}
		}
		free_array(line);
		error(cb, COLOR_ERROR);
	}
	return (0);
}

static int	check_param_path(t_cub *cb, char **line, int *status, int k)
{
	if (!ft_strncmp(line[0], cb->map.param[k], 3))
	{
		if (!cb->map.par[k])
		{
			if (!check_path(cb, line[1], cb->map.param[k]))
			{
				*status = 1;
				cb->map.par[k] = 1;
				return (1);
			}
		}
		free_array(line);
		error(cb, PATH_ERROR);
	}
	return (0);
}

static void	check_param_path_color(t_cub *cb, char **line, int *status)
{
	int	k;

	k = 0;
	while (cb->map.param[k])
	{
		*status = 0;
		if (k < 4)
		{
			if (check_param_path(cb, line, status, k))
				break ;
		}
		else
		{
			if (check_param_color(cb, line, status, k))
				break ;
		}
		k++;
	}
}

int	check_param2(t_cub *cb, int i)
{
	char	**line;
	int		status;

	status = 0;
	line = ft_split(cb->map.file[i], ' ');
	if (!line)
		error(cb, MALLOC_ERROR);
	if (ft_maplen(line) > 2 && line[2][0] != '\n')
		error(cb, TOO_MANY_ARG_ON_LINE);
	if (!ft_strncmp(line[0], "1", 1))
	{
		free_array(line);
		return (1);
	}
	check_param_path_color(cb, line, &status);
	if (!status && ft_strncmp(line[0], "\n", 1))
	{
		free_array(line);
		error(cb, PARAM_ERROR);
	}
	free_array(line);
	return (0);
}
