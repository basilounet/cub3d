/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:47:10 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/28 15:27:27 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	handle_fov_change(t_cub *cb, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_O && keydata.action == MLX_REPEAT
		&& cb->player.fov < 120)
		cb->player.fov += 2;
	if (keydata.key == MLX_KEY_P && keydata.action == MLX_REPEAT
		&& cb->player.fov > 30)
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
	draw_map(cb, cb->minimap);
	if (cb->flags & PAUSE)
		return ;
	update_player_facing(cb);
	change_pos(cb);
	raycaster(cb);
}

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_cub	*cb;

	cb = (t_cub *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		change_pause_state(cb);
	handle_fov_change(cb, keydata);
}

void	ft_mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods,
		void *param)
{
	t_cub	*cb;

	(void)mods;
	cb = (t_cub *)param;
	if (cb->flags & PAUSE && button == MLX_MOUSE_BUTTON_LEFT
		&& action == MLX_PRESS)
		pause_button_press(cb);
}
