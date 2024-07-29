/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:05:06 by bvasseur          #+#    #+#             */
/*   Updated: 2024/07/17 10:23:36 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

static void	pixel_pause(t_cub *cb)
{
	int	i;

	i = 0;
	while (i < WIDTH * HEIGHT * 4)
	{
		cb->pause.image->pixels[i++] = (PAUSE_MENU_COLOR >> 24) & 255;
		cb->pause.image->pixels[i++] = (PAUSE_MENU_COLOR >> 16) & 255;
		cb->pause.image->pixels[i++] = (PAUSE_MENU_COLOR >> 8) & 255;
		cb->pause.image->pixels[i++] = PAUSE_MENU_COLOR & 255;
	}
}

static void	draw_pause_rectangle(t_cub *cb)
{
	draw_rectangle(cb->pause.image, set_vector(WIDTH * .035, \
	HEIGHT * .4), set_vector(WIDTH * .025, HEIGHT * .045), cb->map.floor_color);
	draw_empty_rectangle(cb->pause.image, set_vector(WIDTH * .035, \
	HEIGHT * .4), set_vector(WIDTH * .025, HEIGHT * .045), 0xFF);
	draw_rectangle(cb->pause.image, set_vector(WIDTH * .94225, \
	HEIGHT * .4), set_vector(WIDTH * .025, HEIGHT * .045), \
	cb->map.ceiling_color);
	draw_empty_rectangle(cb->pause.image, set_vector(WIDTH * .94225, \
	HEIGHT * .4), set_vector(WIDTH * .025, HEIGHT * .045), 0xFF);
}

void	create_pause_screen(t_cub *cb)
{
	cb->pause.image = mlx_new_image(cb->mlx, WIDTH, HEIGHT);
	if (!cb->pause.image)
		error(cb, MLX_ERROR);
	pixel_pause(cb);
	cb->pause.buttons_count = 8;
	cb->pause.buttons = ft_calloc(sizeof(t_button), cb->pause.buttons_count
			+ 1);
	cb->pause.sliders_count = 14;
	cb->pause.sliders = ft_calloc(sizeof(t_slider), cb->pause.sliders_count
			+ 1);
	if (!cb->pause.buttons || !cb->pause.sliders)
		error(cb, MALLOC_ERROR);
	if (mlx_image_to_window(cb->mlx, cb->pause.image, 0, 0) == -1)
		error(cb, MLX_ERROR);
	create_buttons(cb);
	create_sliders(cb);
	draw_pause_rectangle(cb);
}

void	pause_button_press(t_cub *cb, action_t action)
{
	int	i;

	if (cb->flags & FIRST_PLAY)
	{
		cb->player.facing = set_vector(cb->player.facing.x * cos(.0015)
				- cb->player.facing.y * sin(.0015), cb->player.facing.x
				* sin(.0015) + cb->player.facing.y * cos(.0015));
		cb->player.plane = set_vector(cb->player.plane.x * cos(.0015)
				- cb->player.plane.y * sin(.0015), cb->player.plane.x
				* sin(.0015) + cb->player.plane.y * cos(.0015));
		raycaster(cb);
	}
	i = -1;
	while (action == MLX_PRESS && ++i < cb->pause.buttons_count)
		if (is_in_button(cb, cb->pause.buttons[i].pos,
				cb->pause.buttons[i].size) && cb->pause.buttons[i].callback)
			cb->pause.buttons[i].callback(cb);
	i = -1;
	while (cb->flags & MOUSE_PRESSED && ++i < cb->pause.sliders_count)
		if (is_in_button(cb, cb->pause.sliders[i].pos,
				cb->pause.sliders[i].size) && cb->pause.sliders[i].callback)
			cb->pause.sliders[i].callback(cb, &cb->pause.sliders[i]);
}

void	change_pause_state(t_cub *cb)
{
	int	i;

	cb->flags = (cb->flags ^ PAUSE) - ((cb->flags & FIRST_PLAY));
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
