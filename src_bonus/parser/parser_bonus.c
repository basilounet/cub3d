/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:32:52 by bvasseur          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/07/29 20:48:51 by bvasseur         ###   ########.fr       */
=======
/*   Updated: 2024/07/31 09:09:17 by amolbert         ###   ########.fr       */
>>>>>>> 74fd9b119d0e5b28523db29d9e062ab58f7cad87
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

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

void	set_entities(t_cub *cb)
{
	int	k;
	int	i;

	k = 0;
	i = 0;
	cb->entities = ft_calloc(sizeof(t_entity), (cb->nb_of_entities + 1));
	if (!cb->entities)
		error(cb, MALLOC_ERROR);
	while (cb->map.map[i])
	{
		save_entities(cb, i, &k);
		i++;
	}
}

static void	set_doors(t_cub *cb)
{
	int	count;
	int	i;
	int	j;

	cb->doors = ft_calloc(sizeof(t_door), cb->nb_of_doors + 1);
	if (!cb->doors)
		error(cb, MALLOC_ERROR);
	i = 0;
	count = 0;
	while (cb->map.map[i])
	{
		j = 0;
		while (cb->map.map[i][j])
		{
			if (cb->map.map[i][j] == 'D')
				cb->doors[count++] = (t_door){{j, i}, cb->map.map[i][j + 1] == \
				'1' && cb->map.map[i][j + 1] == '1', CLOSE, 1, 0.5};
			j++;
		}
		i++;
	}
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
	load_png(cb);
	set_param(cb);
	check_param(cb);
	check_map(cb);
	set_entities(cb);
	set_doors(cb);
}
