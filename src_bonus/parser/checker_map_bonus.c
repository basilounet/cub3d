/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_map_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:10:19 by amolbert          #+#    #+#             */
/*   Updated: 2024/06/28 17:09:31 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

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
				&& !ft_isplayer(cb->map.map[i][j]) && cb->map.map[i][j] != ' ')
				error(cb, BADCHAR_ERROR);
			if (ft_isplayer(cb->map.map[i][j]))
				check_player(cb, &status, i, j);
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

	(void)j;
	len = ft_strlen(cb->map.map[i]);
	height = ft_maplen(cb->map.map);
	if (i == 0 || i == height - 1 || j == 0 || j == len - 1)
		error(cb, CLOSED_ERROR);
}

void	check_near_char(t_cub *cb, int i, int j)
{
	if (cb->map.map[i - 1][j] == '\0' || cb->map.map[i + 1][j] == '\0')
		error(cb, CLOSED_ERROR);
	if (cb->map.map[i][j - 1] == '\0' || cb->map.map[i][j + 1] == '\0')
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
			if (cb->map.map[i][j] != '1' && cb->map.map[i][j] != ' ')
			{
				check_borders(cb, i, j);
				check_near_char(cb, i, j);
			}
			j++;
		}
		i++;
	}
}
