/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:47:10 by bvasseur          #+#    #+#             */
/*   Updated: 2024/07/31 16:45:27 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	change_map_state(t_cub *cb, int action, double w, double h)
{
	static double	last_width = MINIMAP_WIDTH;
	static double	last_height = MINIMAP_HEIGHT;

	if (action == 1 && w > 0)
		last_width = w;
	if (action == 1 && h > 0)
		last_height = h;
	if (action == 1)
		return ;
	cb->flags ^= FULL_MAP;
	if ((cb->flags & FULL_MAP) != 0)
	{
		cb->minimap.image->instances[0].x = 10;
		cb->minimap.image->instances[0].y = 10;
		cb->minimap.width = WIDTH - 20;
		cb->minimap.height = HEIGHT - 20;
	}
	else
	{
		cb->minimap.image->instances[0].x = cb->pause.sliders[12].value;
		cb->minimap.image->instances[0].y = cb->pause.sliders[13].value;
		cb->minimap.width = last_width;
		cb->minimap.height = last_height;
	}
	mlx_resize_image(cb->minimap.image, cb->minimap.width, cb->minimap.height);
}

void	ft_loop_hook(void *param)
{
	t_cub	*cb;

	cb = (t_cub *)param;
	draw_map(cb, cb->minimap);
	check_player_collision(cb, cb->player, cb->entities, cb->nb_of_entities);
	if (cb->flags & PAUSE)
		pause_button_press(cb, 0);
	if (cb->flags & PAUSE || cb->flags & DEAD)
		return ;
	update_player_facing(cb);
	change_pos(cb);
	move_enemy(cb);
	if (cb->nb_of_items)
		check_collect_items(cb, cb->player, cb->entities, &cb->nb_of_entities);
	animate_weapon(cb);
	animate_doors(cb);
	player_step_sound(cb);
	raycaster(cb);
}

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_cub	*cb;

	cb = (t_cub *)param;
	if (cb->flags & DEAD && keydata.key == MLX_KEY_ESCAPE && \
		keydata.action == MLX_PRESS)
		mlx_close_window(cb->mlx);
	if (cb->flags & DEAD)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		change_pause_state(cb);
	if (keydata.key == MLX_KEY_F && keydata.action == MLX_PRESS)
		cb->flags ^= LIGHT_ON;
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
		change_map_state(cb, 0, 0, 0);
	god_mod(cb, keydata);
}

void	ft_mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods,
		void *param)
{
	t_cub	*cb;

	(void)mods;
	cb = (t_cub *)param;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
		cb->flags |= MOUSE_PRESSED;
	else if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_RELEASE
		&& cb->flags & MOUSE_PRESSED)
		cb->flags ^= MOUSE_PRESSED;
	if (cb->flags & DEAD)
		return ;
	if (cb->flags & PAUSE && button == MLX_MOUSE_BUTTON_LEFT && \
		action == MLX_PRESS)
		pause_button_press(cb, action);
	if (!(cb->flags & PAUSE) && button == MLX_MOUSE_BUTTON_RIGHT && \
		action == MLX_PRESS)
		change_weapon(cb);
}
