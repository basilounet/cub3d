/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sliders_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:00:38 by bvasseur          #+#    #+#             */
/*   Updated: 2024/07/17 10:16:54 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

static void	create_slider(t_cub *cb, t_slider sketch, t_slider *final)
{
	sketch.slider.pos = sketch.pos;
	sketch.slider.size = sketch.size;
	sketch.value = ft_clamp(sketch.value, sketch.min, sketch.max);
	sketch.percentage = (sketch.value
			- sketch.min) / (double)(sketch.max - sketch.min);
	sketch.range = set_vector(sketch.pos.x + sketch.size.x * sketch.range.x,
			sketch.pos.x + sketch.size.x * sketch.range.y);
	sketch.button.pos = set_vector(sketch.range.x + (sketch.range.y
				- sketch.range.x) * sketch.percentage + sketch.button_offset.x,
			sketch.pos.y + sketch.button_offset.y);
	sketch.button.size = set_vector(sketch.size.x * sketch.button.size.x,
			sketch.size.y * sketch.button.size.y);
	*final = sketch;
	create_button(cb, sketch.slider, &final->slider);
	create_button(cb, sketch.button, &final->button);
}

static void	create_floor_color_sliders(t_cub *cb)
{
	create_slider(cb, (t_slider){{.075, .475}, {.2, .04}, {{0}, {0}, {.1, 1}, \
		{-.2, 0}, "R", "textures/slider.png", 0, 0, 0, 0}, {{0}, \
		{.1, .8}, {0}, {0}, "", "textures/slider_button.png", 0, 0, 0, 0}, \
		{0, 0}, {.09, .8}, &floor_red_slider, 0, 255, \
		(cb->map.floor_color >> 24) & 255, 0}, &cb->pause.sliders[6]);
	create_slider(cb, (t_slider){{.075, .575}, {.2, .04}, {{0}, {0}, {.1, 1}, \
		{-.2, 0}, "G", "textures/slider.png", 0, 0, 0, 0}, {{0}, \
		{.1, .8}, {0}, {0}, "", "textures/slider_button.png", 0, 0, 0, 0}, \
		{0, 0}, {.09, .8}, &floor_green_slider, 0, 255, \
		(cb->map.floor_color >> 16) & 255, 0}, &cb->pause.sliders[7]);
	create_slider(cb, (t_slider){{.075, .675}, {.2, .04}, {{0}, {0}, {.1, 1}, \
		{-.2, 0}, "B", "textures/slider.png", 0, 0, 0, 0}, {{0}, \
		{.1, .8}, {0}, {0}, "", "textures/slider_button.png", 0, 0, 0, 0}, \
		{0, 0}, {.09, .8}, &floor_blue_slider, 0, 255, \
		(cb->map.floor_color >> 8) & 255, 0}, &cb->pause.sliders[8]);
}

static void	create_ceil_color_sliders(t_cub *cb)
{
	create_slider(cb, (t_slider){{.725, .475}, {.2, .04}, {{0}, {0}, {.1, 1}, \
		{1.1, 0}, "R", "textures/slider.png", 0, 0, 0, 0}, {{0}, \
		{.1, .8}, {0}, {0}, "", "textures/slider_button.png", 0, 0, 0, 0}, \
		{0, 0}, {.09, .8}, &ceiling_red_slider, 0, 255, \
		(cb->map.ceiling_color >> 24) & 255, 0}, &cb->pause.sliders[9]);
	create_slider(cb, (t_slider){{.725, .575}, {.2, .04}, {{0}, {0}, {.1, 1}, \
		{1.1, 0}, "G", "textures/slider.png", 0, 0, 0, 0}, {{0}, \
		{.1, .8}, {0}, {0}, "", "textures/slider_button.png", 0, 0, 0, 0}, \
		{0, 0}, {.09, .8}, &ceiling_green_slider, 0, 255, \
		(cb->map.ceiling_color >> 16) & 255, 0}, &cb->pause.sliders[10]);
	create_slider(cb, (t_slider){{.725, .675}, {.2, .04}, {{0}, {0}, {.1, 1}, \
		{1.1, 0}, "B", "textures/slider.png", 0, 0, 0, 0}, {{0}, \
		{.1, .8}, {0}, {0}, "", "textures/slider_button.png", 0, 0, 0, 0}, \
		{0, 0}, {.09, .8}, &ceiling_blue_slider, 0, 255, \
		(cb->map.ceiling_color >> 8) & 255, 0}, &cb->pause.sliders[11]);
}

static void	create_minimap_sliders(t_cub *cb)
{
	create_slider(cb, (t_slider){{.725, .075}, {.2, .04}, {{0}, {0}, {.6, .8}, \
		{.2, -.8}, "Minimap widht", "textures/slider.png", 0, 0, 0, 0}, {{0}, \
		{.1, .8}, {0}, {0}, "", "textures/slider_button.png", 0, 0, 0, 0}, \
		{0, 0}, {.09, .8}, &mm_width_slider, 50, WIDTH - 20, cb->minimap.width, \
		0}, &cb->pause.sliders[3]);
	create_slider(cb, (t_slider){{.725, .175}, {.2, .04}, {{0}, {0}, {.6, .8}, \
		{.2, -.8}, "Minimap height", "textures/slider.png", 0, 0, 0, 0}, {{0}, \
		{.1, .8}, {0}, {0}, "", "textures/slider_button.png", 0, 0, 0, 0}, \
		{0, 0}, {.09, .8}, &mm_height_slider, 50, HEIGHT - 20, \
		cb->minimap.height, 0}, &cb->pause.sliders[4]);
	create_slider(cb, (t_slider){{.725, .275}, {.2, .04}, {{0}, {0}, {.6, .8}, \
		{.2, -.8}, "Minimap zoom", "textures/slider.png", 0, 0, 0, 0}, {{0}, \
		{.1, .8}, {0}, {0}, "", "textures/slider_button.png", 0, 0, 0, 0}, \
		{0, 0}, {.09, .8}, &mm_zoom_slider, 5, 29, cb->minimap.square_size, 0}, \
		&cb->pause.sliders[5]);
	create_slider(cb, (t_slider){{.675, .8}, {.275, .04}, {{0}, {0}, {.6, .8}, \
		{.2, -.85}, "Minimap pos x", "textures/slider.png", 0, 0, 0, 0}, {{0}, \
		{.1, .8}, {0}, {0}, "", "textures/slider_button.png", 0, 0, 0, 0}, \
		{0, 0}, {.09, .8}, &mm_pos_x_slider, 10, WIDTH - 60, 10, 0}, \
		&cb->pause.sliders[12]);
	create_slider(cb, (t_slider){{.675, .9}, {.275, .04}, {{0}, {0}, {.6, .8}, \
		{.2, -.85}, "Minimap pos y", "textures/slider.png", 0, 0, 0, 0}, {{0}, \
		{.1, .8}, {0}, {0}, "", "textures/slider_button.png", 0, 0, 0, 0}, \
		{0, 0}, {.09, .8}, &mm_pos_y_slider, 10, HEIGHT - 60, 10, 0}, \
		&cb->pause.sliders[13]);
}

void	create_sliders(t_cub *cb)
{
	create_slider(cb, (t_slider){{.075, .075}, {.2, .04}, {{0}, {0}, {.3, .8}, \
		{.35, -.8}, "FOV", "textures/slider.png", 0, 0, 0, 0}, {{0}, \
		{.1, .8}, {0}, {0}, "", "textures/slider_button.png", 0, 0, 0, 0}, \
		{0, 0}, {.09, .8}, &fov_slider, 30, 120, cb->player.fov, 0}, \
		&cb->pause.sliders[0]);
	create_slider(cb, (t_slider){{.075, .175}, {.2, .04}, {{0}, {0}, {.8, .8}, \
		{.1, -.8}, "Mouse sensibility", "textures/slider.png", 0, 0, 0, 0}, \
		{{0}, {.1, .8}, {0}, {0}, "", "textures/slider_button.png", 0, 0, 0, \
		0}, {0, 0}, {.09, .8}, &mouse_sensisibility_slider, 1, 16, \
		cb->player.mouse_rotation_speed * 10000, 0}, &cb->pause.sliders[1]);
	create_slider(cb, (t_slider){{.075, .275}, {.2, .04}, {{0}, {0}, {.8, .8}, \
		{.1, -.8}, "keyboard sensibility", "textures/slider.png", 0, 0, 0, 0}, \
		{{0}, {.1, .8}, {0}, {0}, "", "textures/slider_button.png", 0, 0, \
		0, 0}, {0, 0}, {.09, .8}, &keyboard_sensisibility_slider, 1, 16, \
		cb->player.key_rotation_speed * 100, 0}, &cb->pause.sliders[2]);
	create_floor_color_sliders(cb);
	create_ceil_color_sliders(cb);
	create_minimap_sliders(cb);
}
