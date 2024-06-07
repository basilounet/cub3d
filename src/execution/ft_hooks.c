/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:47:10 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/07 20:34:52 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	ft_loop_hook(void *param)
{
	t_cub	*cb;

	cb = (t_cub *)param;
	if (mlx_is_key_down(cb->mlx, MLX_KEY_A))
		change_pos(cb, -0.15, 0);
	if (mlx_is_key_down(cb->mlx, MLX_KEY_D))
		change_pos(cb, 0.15, 0);
	if (mlx_is_key_down(cb->mlx, MLX_KEY_W))
		change_pos(cb, 0, -0.15);
	if (mlx_is_key_down(cb->mlx, MLX_KEY_S))
		change_pos(cb, 0, 0.15);
}

void	ft_key_hook(mlx_key_data_t keydata, void* param)
{
	t_cub	*cb;

	cb = (t_cub *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(cb->mlx);
}
