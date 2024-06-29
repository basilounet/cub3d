/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:06:36 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/29 17:18:17 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	is_in_button(t_cub *cb, t_button button)
{
	int	x;
	int	y;

	mlx_get_mouse_pos(cb->mlx, &x, &y);
	return (x >= cb->mlx->width * button.pos.x && x < cb->mlx->width * button.pos.x
		+ cb->mlx->width * button.size.x && y >= cb->mlx->height * button.pos.y
		&& y < cb->mlx->height * button.pos.y + cb->mlx->height * button.size.y);
}
