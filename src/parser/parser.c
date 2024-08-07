/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:32:52 by bvasseur          #+#    #+#             */
/*   Updated: 2024/07/31 16:20:24 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	check_param(t_cub *cb)
{
	int		i;

	i = 0;
	while (cb->map.file[i])
	{
		if (check_param2(cb, i))
			break ;
		i++;
	}
	param_full(cb);
}

void	check_map(t_cub *cb)
{
	cb->map.height = ft_maplen(cb->map.file);
	save_map(cb, cb->map.height);
	check_blank_line(cb);
	check_char(cb);
	check_closed_map(cb);
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
	cb->map.height_file = ft_maplen(cb->map.file);
	set_param(cb);
	check_param(cb);
	check_map(cb);
}
