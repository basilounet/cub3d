/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_callback.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:20:32 by bvasseur          #+#    #+#             */
/*   Updated: 2024/07/04 12:50:46 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	exit_callback(t_cub *cb)
{
	mlx_close_window(cb->mlx);
}

void	scale_1_3(t_cub *cb)
{
	int	width;
	int	height;

	mlx_get_monitor_size(0, &width, &height);
	mlx_set_window_size(cb->mlx, width / 3, height / 3);
}

void	scale_2_3(t_cub *cb)
{
	int	width;
	int	height;

	mlx_get_monitor_size(0, &width, &height);
	mlx_set_window_size(cb->mlx, width * 2 / 3, height * 2 / 3);
}

void	scale_1_1(t_cub *cb)
{
	int	width;
	int	height;

	mlx_get_monitor_size(0, &width, &height);
	mlx_set_window_size(cb->mlx, width, height - 100);
}
