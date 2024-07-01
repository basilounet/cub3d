/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:41:32 by amolbert          #+#    #+#             */
/*   Updated: 2024/06/25 14:42:20 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	ft_isplayer(int c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

static void	save_player(t_cub *cb, char c, int i, int j)
{
	cb->player.pos = set_vector(j + 0.5, i + 0.5);
	if (c == 'N')
		cb->player.facing = set_vector(0, -1);
	if (c == 'S')
		cb->player.facing = set_vector(0, 1);
	if (c == 'E')
		cb->player.facing = set_vector(1, 0);
	if (c == 'W')
		cb->player.facing = set_vector(-1, 0);
}

void	check_player(t_cub *cb, int *status, int i, int j)
{
	if (*status)
		error(cb, PLAYER_ERROR);
	*status = 1;
	save_player(cb, cb->map.map[i][j], i, j);
	cb->map.map[i][j] = '0';
}
