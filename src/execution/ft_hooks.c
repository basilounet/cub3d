/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:47:10 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/23 16:54:59 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	handle_fov_change(t_cub *cb, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_O && keydata.action == MLX_REPEAT)
		cb->player.fov += 2;
	if (keydata.key == MLX_KEY_P && keydata.action == MLX_REPEAT)
		cb->player.fov -= 2;
	if (keydata.key == MLX_KEY_P || keydata.key == MLX_KEY_O)
	{
		cb->player.length_plane = tan(cb->player.fov / 2 * (M_PI / 180.0));
		cb->player.plane.x = cb->player.length_plane * -cb->player.facing.y;
		cb->player.plane.y = cb->player.length_plane * cb->player.facing.x;
	}
}

void	ft_loop_hook(void *param)
{
	t_cub	*cb;

	cb = (t_cub *)param;
	update_player_facing(cb);
	change_pos(cb);
	if (BONUS)
		draw_map(cb);
	raycaster(cb);
}

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_cub	*cb;

	cb = (t_cub *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(cb->mlx);
	handle_fov_change(cb, keydata);
}
