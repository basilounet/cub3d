/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:21:23 by amolbert          #+#    #+#             */
/*   Updated: 2024/07/16 15:25:09 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	check_door(t_cub *cb, int i, int j)
{
	if ((cb->map.map[i + 1][j] == '1' && cb->map.map[i - 1][j] == '1') || \
	(cb->map.map[i][j + 1] && cb->map.map[i][j - 1] == '1'))
		return ;
	error(cb, DOOR_ERROR);
}
