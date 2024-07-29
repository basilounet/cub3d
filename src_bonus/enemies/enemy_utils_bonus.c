/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:07:03 by amolbert          #+#    #+#             */
/*   Updated: 2024/07/17 14:18:37 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	update_pos(t_cub *cb, t_vector *new_pos, t_vector pos, t_vector old_pos)
{
	if (cb->map.map[(int)(pos.y + .2)][(int)pos.x] == '1')
		new_pos->y = ceil(pos.y) - .2;
	if (cb->map.map[(int)(pos.y - .2)][(int)pos.x] == '1')
		new_pos->y = floor(pos.y) + .2;
	if (cb->map.map[(int)pos.y][(int)(pos.x + .2)] == '1')
		new_pos->x = ceil(pos.x) - .2;
	if (cb->map.map[(int)pos.y][(int)(pos.x - .2)] == '1')
		new_pos->x = floor(pos.x) + .2;
	if (cb->map.map[(int)new_pos->y][(int)new_pos->x] == '1')
		*new_pos = old_pos;
}
