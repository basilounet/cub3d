/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_callback.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:20:32 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/29 17:16:33 by bvasseur         ###   ########.fr       */
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
    // WIDTH = width / 3;
    // HEIGHT = height / 3;
	mlx_set_window_size(cb->mlx, width / 3, height / 3);
    // mlx_resize_image(cb->image, width / 3, height / 3);
    // create_pause_screen(cb, 1);
	// replace_buttons(cb);
}

void	scale_2_3(t_cub *cb)
{
	int	width;
	int	height;

	mlx_get_monitor_size(0, &width, &height);
    // WIDTH = width * 2 / 3;
    // HEIGHT = height * 2 / 3;
	mlx_set_window_size(cb->mlx, width * 2 / 3, height * 2 / 3);
    // mlx_resize_image(cb->image, width * 2 / 3, height * 2 / 3);
    // create_pause_screen(cb, 1);
	// replace_buttons(cb);
}

void	scale_1_1(t_cub *cb)
{
	int	width;
	int	height;

	mlx_get_monitor_size(0, &width, &height);
    // WIDTH = width;
    // HEIGHT = height;
	mlx_set_window_size(cb->mlx, width, height);
    // mlx_resize_image(cb->image, width, height);
    // create_pause_screen(cb, 1);
	// replace_buttons(cb);
}
