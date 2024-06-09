/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:47:10 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/09 16:13:07 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	update_player_facing(t_cub *cb)
{
	double	angle;
	double	current_angle;

	angle = 0;
	if (mlx_is_key_down(cb->mlx, MLX_KEY_LEFT))
		angle -= ROTATION_SPEED;
	if (mlx_is_key_down(cb->mlx, MLX_KEY_RIGHT))
		angle += ROTATION_SPEED;
	if (angle != 0)
	{
		current_angle = atan2(cb->player.facing.y, cb->player.facing.x);
		current_angle += angle;
		cb->player.facing.x = cos(current_angle);
		cb->player.facing.y = sin(current_angle);
	}
}

void	ft_loop_hook(void *param)
{
	t_cub	*cb;

	cb = (t_cub *)param;
	update_player_facing(cb);
	change_pos(cb);
	//printf("facing x : %f, y : %f\n", cb->player.facing.x, cb->player.facing.y);
	draw_map(cb);
}

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_cub	*cb;

	cb = (t_cub *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(cb->mlx);
}
