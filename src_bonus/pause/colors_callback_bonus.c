/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_callback_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:43:00 by bvasseur          #+#    #+#             */
/*   Updated: 2024/07/17 09:53:58 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	floor_green_slider(t_cub *cb, t_slider *slider)
{
	update_slider_values(cb, slider);
	cb->map.floor_color &= 0xFF00FFFF;
	cb->map.floor_color |= slider->value << 16;
	draw_rectangle(cb->pause.image, set_vector(WIDTH * .035, \
	HEIGHT * .4), set_vector(WIDTH * .025, HEIGHT * .045), cb->map.floor_color);
	draw_empty_rectangle(cb->pause.image, set_vector(WIDTH * .035, \
	HEIGHT * .4), set_vector(WIDTH * .025, HEIGHT * .045), 0xFF);
	raycaster(cb);
}

void	floor_blue_slider(t_cub *cb, t_slider *slider)
{
	update_slider_values(cb, slider);
	cb->map.floor_color &= 0xFFFF00FF;
	cb->map.floor_color |= slider->value << 8;
	draw_rectangle(cb->pause.image, set_vector(WIDTH * .035, \
	HEIGHT * .4), set_vector(WIDTH * .025, HEIGHT * .045), cb->map.floor_color);
	draw_empty_rectangle(cb->pause.image, set_vector(WIDTH * .035, \
	HEIGHT * .4), set_vector(WIDTH * .025, HEIGHT * .045), 0xFF);
	raycaster(cb);
}

void	ceiling_red_slider(t_cub *cb, t_slider *slider)
{
	update_slider_values(cb, slider);
	cb->map.ceiling_color &= 0x00FFFFFF;
	cb->map.ceiling_color |= slider->value << 24;
	draw_rectangle(cb->pause.image, set_vector(WIDTH * .94225, \
	HEIGHT * .4), set_vector(WIDTH * .025, HEIGHT * .045), \
	cb->map.ceiling_color);
	draw_empty_rectangle(cb->pause.image, set_vector(WIDTH * .94225, \
	HEIGHT * .4), set_vector(WIDTH * .025, HEIGHT * .045), 0xFF);
	raycaster(cb);
}

void	ceiling_green_slider(t_cub *cb, t_slider *slider)
{
	update_slider_values(cb, slider);
	cb->map.ceiling_color &= 0xFF00FFFF;
	cb->map.ceiling_color |= slider->value << 16;
	draw_rectangle(cb->pause.image, set_vector(WIDTH * .94225, \
	HEIGHT * .4), set_vector(WIDTH * .025, HEIGHT * .045), \
	cb->map.ceiling_color);
	draw_empty_rectangle(cb->pause.image, set_vector(WIDTH * .94225, \
	HEIGHT * .4), set_vector(WIDTH * .025, HEIGHT * .045), 0xFF);
	raycaster(cb);
}

void	ceiling_blue_slider(t_cub *cb, t_slider *slider)
{
	update_slider_values(cb, slider);
	cb->map.ceiling_color &= 0xFFFF00FF;
	cb->map.ceiling_color |= slider->value << 8;
	draw_rectangle(cb->pause.image, set_vector(WIDTH * .94225, \
	HEIGHT * .4), set_vector(WIDTH * .025, HEIGHT * .045), \
	cb->map.ceiling_color);
	draw_empty_rectangle(cb->pause.image, set_vector(WIDTH * .94225, \
	HEIGHT * .4), set_vector(WIDTH * .025, HEIGHT * .045), 0xFF);
	raycaster(cb);
}
