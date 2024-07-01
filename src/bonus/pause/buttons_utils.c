/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:06:36 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/30 13:32:30 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	is_in_button(t_cub *cb, t_vector pos, t_vector size)
{
	int	x;
	int	y;

	mlx_get_mouse_pos(cb->mlx, &x, &y);
	return (x >= cb->mlx->width * pos.x && x < cb->mlx->width * pos.x
		+ cb->mlx->width * size.x && y >= cb->mlx->height * pos.y
		&& y < cb->mlx->height * pos.y + cb->mlx->height * size.y);
}

// double	get_percentage_pos(t_vector pos, t_vector size, double p)
// {
// 	return (ft_clamp(size.x * p, pos.x, ))
// }
