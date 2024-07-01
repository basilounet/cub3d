/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:05:06 by bvasseur          #+#    #+#             */
/*   Updated: 2024/07/01 16:06:19 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	place_button(t_button button)
{
	if (button.bg)
	{
		mlx_resize_image(button.bg, WIDTH * button.size.x, HEIGHT
			* button.size.y);
		button.bg->instances[0].x = WIDTH * button.pos.x;
		button.bg->instances[0].y = HEIGHT * button.pos.y;
	}
	if (button.text_img)
	{
		mlx_resize_image(button.text_img, WIDTH * button.size.x
			* button.text_size.x, HEIGHT * button.size.y * button.text_size.y);
		button.text_img->instances[0].x = WIDTH * button.pos.x + WIDTH
			* button.size.x * button.text_offset.x;
		button.text_img->instances[0].y = HEIGHT * button.pos.y + HEIGHT
			* button.size.y * button.text_offset.y;
	}
}

void	create_button(t_cub *cb, t_button sketch, t_button *final)
{
	*final = sketch;
	final->text = ft_strdup(sketch.text);
	final->txt_name = ft_strdup(sketch.txt_name);
	if (sketch.txt_name && sketch.txt_name[0])
	{
		final->txt = mlx_load_png(final->txt_name);
		if (final->txt)
			final->bg = mlx_texture_to_image(cb->mlx, final->txt);
		if (mlx_image_to_window(cb->mlx, final->bg, 0, 0) == -1)
			error(cb, MLX_ERROR);
		final->bg->enabled = cb->flags & PAUSE;
	}
	final->text_img = mlx_put_string(cb->mlx, final->text, final->pos.x,
			final->pos.y);
	if (final->text_img)
		final->text_img->enabled = cb->flags & PAUSE;
	if (!final->text || !final->txt_name || (final->txt_name
			&& final->txt_name[0] && (!final->txt || !final->bg))
		|| (final->text && final->text[0] && !final->text_img))
		error(cb, MALLOC_ERROR);
	place_button(*final);
}

void	create_buttons(t_cub *cb)
{
	create_button(cb, (t_button){{.4, .775}, {.2, .15}, {.525, .575}, {.22,
		.125}, "Exit", "textures/red_button.png", &exit_callback, 0, 0, 0},
		&cb->pause.buttons[0]);
	create_button(cb, (t_button){{.425, .5}, {.15, .1}, {.8, .8}, {.1, 0},
		"Play", "textures/red_button.png", &change_pause_state, 0, 0, 0},
		&cb->pause.buttons[1]);
	create_button(cb, (t_button){{.025, .825}, {.1, .05}, {.8, .8}, {.1, .04},
		"1 / 3", "textures/red_button.png", &scale_1_3, 0, 0, 0},
		&cb->pause.buttons[2]);
	create_button(cb, (t_button){{0.15, 0.825}, {.1, .05}, {.8, .8}, {.1, .04},
		"2 / 3", "textures/red_button.png", &scale_2_3, 0, 0, 0},
		&cb->pause.buttons[3]);
	create_button(cb, (t_button){{.275, .825}, {.1, .05}, {.8, .8}, {.1, .04},
		"1 / 1", "textures/red_button.png", &scale_1_1, 0, 0, 0},
		&cb->pause.buttons[4]);
	create_button(cb, (t_button){{.375, .2}, {.25, .2}, {1, 1.3}, {0, -.3},
		"cub3D", "", 0, 0, 0, 0}, &cb->pause.buttons[5]);
}

void	create_slider(t_cub *cb, t_slider sketch, t_slider *final)
{
	sketch.slider.pos = sketch.pos;
	sketch.slider.size = sketch.size;
	sketch.percentage = (ft_clamp(sketch.value, sketch.min, sketch.max - 1)
			- sketch.min) / (double)(sketch.max - sketch.min);
	sketch.percentage_range = set_vector(sketch.pos.x + sketch.size.x * sketch.percentage_range.x, sketch.pos.x + sketch.size.x * sketch.percentage_range.y);
	sketch.button.pos = set_vector(sketch.pos.x + sketch.size.x
			* sketch.percentage + sketch.button_offset.x, sketch.pos.y
			+ sketch.button_offset.y);
	sketch.button.size = set_vector(sketch.size.x * sketch.button.size.x,
			sketch.size.y * sketch.button.size.y);
	*final = sketch;
	create_button(cb, sketch.slider, &final->slider);
	create_button(cb, sketch.button, &final->button);
}

void	create_sliders(t_cub *cb)
{
	create_slider(cb, (t_slider){{.1, .1}, {.2, .05}, {{0}, {0}, {.1, 1}, {-.15,
		0}, "R", "textures/yellow_slider.png", 0, 0, 0, 0}, {{0}, {.1, .8}, {0},
		{0}, "", "textures/green_button.png", 0, 0, 0, 0}, {0, 0}, {.025, .8}, NULL,
		0, 256, 256, 0}, &cb->pause.sliders[0]);
}

void	create_pause_screen(t_cub *cb)
{
	int	i;

	cb->pause.image = mlx_new_image(cb->mlx, WIDTH, HEIGHT);
	if (!cb->pause.image)
		error(cb, MLX_ERROR);
	i = 0;
	while (i < WIDTH * HEIGHT * 4)
	{
		cb->pause.image->pixels[i] = (PAUSE_MENU_COLOR >> 24) & 255;
		cb->pause.image->pixels[i + 1] = (PAUSE_MENU_COLOR >> 16) & 255;
		cb->pause.image->pixels[i + 2] = (PAUSE_MENU_COLOR >> 8) & 255;
		cb->pause.image->pixels[i + 3] = PAUSE_MENU_COLOR & 255;
		i += 4;
	}
	cb->pause.image->enabled = cb->flags & PAUSE;
	cb->pause.buttons_count = 6;
	cb->pause.buttons = ft_calloc(sizeof(t_button), cb->pause.buttons_count
			+ 1);
	cb->pause.sliders_count = 12;
	cb->pause.sliders = ft_calloc(sizeof(t_slider), cb->pause.sliders_count
			+ 1);
	if (!cb->pause.buttons || !cb->pause.sliders)
		error(cb, MALLOC_ERROR);
	mlx_image_to_window(cb->mlx, cb->pause.image, 0, 0);
	create_buttons(cb);
	create_sliders(cb);
}

void	pause_button_press(t_cub *cb)
{
	int	i;

	i = -1;
	while (++i < cb->pause.buttons_count)
		if (is_in_button(cb, cb->pause.buttons[i].pos,
				cb->pause.buttons[i].size) && cb->pause.buttons[i].callback)
			cb->pause.buttons[i].callback(cb);
}

void	change_pause_state(t_cub *cb)
{
	int	i;

	cb->flags ^= PAUSE;
	cb->pause.image->enabled = cb->flags & PAUSE;
	mlx_set_mouse_pos(cb->mlx, cb->mlx->width / 2, cb->mlx->height / 2);
	i = -1;
	while (++i < cb->pause.buttons_count)
	{
		if (cb->pause.buttons[i].text_img)
			cb->pause.buttons[i].text_img->enabled = cb->flags & PAUSE;
		if (cb->pause.buttons[i].bg)
			cb->pause.buttons[i].bg->enabled = cb->flags & PAUSE;
	}
	i = -1;
	while (++i < cb->pause.sliders_count)
	{
		if (cb->pause.sliders[i].slider.text_img)
			cb->pause.sliders[i].slider.text_img->enabled = cb->flags & PAUSE;
		if (cb->pause.sliders[i].slider.bg)
			cb->pause.sliders[i].slider.bg->enabled = cb->flags & PAUSE;
		if (cb->pause.sliders[i].button.text_img)
			cb->pause.sliders[i].button.text_img->enabled = cb->flags & PAUSE;
		if (cb->pause.sliders[i].button.bg)
			cb->pause.sliders[i].button.bg->enabled = cb->flags & PAUSE;
	}
}
