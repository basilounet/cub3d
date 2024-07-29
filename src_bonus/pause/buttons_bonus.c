/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:05:07 by bvasseur          #+#    #+#             */
/*   Updated: 2024/07/28 17:12:48 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

static void	place_button(t_button button)
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
		if (!final->bg || mlx_image_to_window(cb->mlx, final->bg, 0, 0) == -1)
			error(cb, MISSING_ESSENTIAL_TEXTURE_ERROR);
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
		.125}, "Exit", "textures/button.png", &exit_callback, 0, 0, 0},
		&cb->pause.buttons[0]);
	create_button(cb, (t_button){{.425, .5}, {.15, .1}, {.8, .8}, {.1, 0},
		"Play", "textures/button.png", &change_pause_state, 0, 0, 0},
		&cb->pause.buttons[1]);
	create_button(cb, (t_button){{.025, .825}, {.1, .05}, {.8, .8}, {.1, .04},
		"1 / 3", "textures/button.png", &scale_1_3, 0, 0, 0},
		&cb->pause.buttons[2]);
	create_button(cb, (t_button){{0.15, 0.825}, {.1, .05}, {.8, .8}, {.1, .04},
		"2 / 3", "textures/button.png", &scale_2_3, 0, 0, 0},
		&cb->pause.buttons[3]);
	create_button(cb, (t_button){{.275, .825}, {.1, .05}, {.8, .8}, {.1, .04},
		"1 / 1", "textures/button.png", &scale_1_1, 0, 0, 0},
		&cb->pause.buttons[4]);
	create_button(cb, (t_button){{.35, .2}, {.3, .275}, {1, 1}, {0, -.3},
		"cub3D", "", 0, 0, 0, 0}, &cb->pause.buttons[5]);
	create_button(cb, (t_button){{.1, .425}, {.15, .05}, {1, 1}, {0, -.3},
		"Floor color", "", 0, 0, 0, 0}, &cb->pause.buttons[6]);
	create_button(cb, (t_button){{.75, .425}, {.15, .05}, {1, 1}, {0, -.3},
		"Ceiling color", "", 0, 0, 0, 0}, &cb->pause.buttons[7]);
}
