/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sliders_callback_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:04:36 by bvasseur          #+#    #+#             */
/*   Updated: 2024/07/15 19:47:49 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	update_slider_values(t_cub *cb, t_slider *slider)
{
	int	x;
	int	y;

	mlx_get_mouse_pos(cb->mlx, &x, &y);
	slider->button.pos = set_vector(ft_fclamp(x / (double)cb->mlx->width - \
		(slider->button.bg->width / 2 / (double)cb->mlx->width), \
		slider->range.x, slider->range.y), slider->button.pos.y);
	slider->percentage = (slider->button.pos.x - slider->range.x) / \
		(double)(slider->range.y - slider->range.x);
	slider->value = (slider->max - slider->min) * slider->percentage + \
		slider->min;
	slider->button.bg->instances[0].x = slider->button.pos.x * WIDTH;
}

void	fov_slider(t_cub *cb, t_slider *slider)
{
	update_slider_values(cb, slider);
	cb->player.length_plane = tan(cb->player.fov / 2 * (M_PI / 180));
	cb->player.plane = set_vector(cb->player.length_plane * \
			-cb->player.facing.y, cb->player.length_plane
			* cb->player.facing.x);
	cb->player.fov = slider->value;
	raycaster(cb);
}

void	mouse_sensisibility_slider(t_cub *cb, t_slider *slider)
{
	update_slider_values(cb, slider);
	cb->player.mouse_rotation_speed = slider->value / (double)10000;
}

void	keyboard_sensisibility_slider(t_cub *cb, t_slider *slider)
{
	update_slider_values(cb, slider);
	cb->player.key_rotation_speed = slider->value / (double)100;
}

void	floor_red_slider(t_cub *cb, t_slider *slider)
{
	update_slider_values(cb, slider);
	cb->map.floor_color &= 0x00FFFFFF;
	cb->map.floor_color |= slider->value << 24;
	draw_rectangle(cb->pause.image, set_vector(WIDTH * .035, \
	HEIGHT * .4), set_vector(WIDTH * .025, HEIGHT * .045), cb->map.floor_color);
	draw_empty_rectangle(cb->pause.image, set_vector(WIDTH * .035, \
	HEIGHT * .4), set_vector(WIDTH * .025, HEIGHT * .045), 0xFF);
	raycaster(cb);
}
