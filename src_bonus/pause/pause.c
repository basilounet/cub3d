/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:05:06 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/29 19:05:15 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	place_buttons(t_cub *cb)
{
	t_button	button;
	int			i;

	i = -1;
	while (++i < cb->pause.buttons_count)
	{
		button = cb->pause.buttons[i];
		if (button.bg)
		{
			mlx_resize_image(button.bg, WIDTH * button.size.x, HEIGHT
				* button.size.y);
			button.bg->instances[0].x = WIDTH * button.pos.x;
			button.bg->instances[0].y = HEIGHT * button.pos.y;
		}
		mlx_resize_image(button.text_img, WIDTH * button.size.x
			* button.text_size.x, HEIGHT * button.size.y * button.text_size.y);
		button.text_img->instances[0].x = WIDTH * button.pos.x + WIDTH
			* button.size.x * button.text_offset.x;
		button.text_img->instances[0].y = HEIGHT * button.pos.y + HEIGHT
			* button.size.y * button.text_offset.y;
	}
}

void	create_button(t_cub *cb, t_button sketch_button, t_button *final_button)
{
	*final_button = (t_button){0};
	final_button->name = ft_strdup(sketch_button.name);
	final_button->pos = sketch_button.pos;
	final_button->size = sketch_button.size;
	final_button->text_size = sketch_button.text_size;
	final_button->text_offset = sketch_button.text_offset;
	final_button->text = ft_strdup(sketch_button.text);
	final_button->txt_name = ft_strdup(sketch_button.txt_name);
	final_button->callback = sketch_button.callback;
	if (sketch_button.txt_name[0])
	{
		final_button->txt = mlx_load_png(final_button->txt_name);
		if (final_button->txt)
			final_button->bg = mlx_texture_to_image(cb->mlx, final_button->txt);
		if (mlx_image_to_window(cb->mlx, final_button->bg, 0, 0) == -1)
			error(cb, MLX_ERROR);
		final_button->bg->enabled = cb->flags & PAUSE;
	}
	final_button->text_img = mlx_put_string(cb->mlx, final_button->text,
			final_button->pos.x, final_button->pos.y);
	final_button->text_img->enabled = cb->flags & PAUSE;
	if (!final_button->name || !final_button->text || !final_button->txt_name
		|| (final_button->txt_name[0] && (!final_button->txt
				|| !final_button->bg)) || !final_button->text_img)
		error(cb, MALLOC_ERROR);
}

void	create_buttons(t_cub *cb)
{
	create_button(cb, (t_button){"exit", {0.4, 0.8}, {0.2, 0.1}, {0.8, 0.8},
		{0.1, 0.04}, "Exit", "textures/red_button.png", &exit_callback, NULL,
		NULL, NULL}, &cb->pause.buttons[0]);
	create_button(cb, (t_button){"play", {0.425, 0.5}, {0.15, 0.1}, {0.8, 0.8},
		{0.1, 0}, "Play", "textures/red_button.png", &change_pause_state, NULL,
		NULL, NULL}, &cb->pause.buttons[1]);
	create_button(cb, (t_button){"1/3", {0.025, 0.825}, {0.1, 0.05}, {0.8, 0.8},
		{0.1, 0.04}, "1 / 3", "textures/red_button.png", &scale_1_3, NULL, NULL,
		NULL}, &cb->pause.buttons[2]);
	create_button(cb, (t_button){"2/3", {0.15, 0.825}, {0.1, 0.05}, {0.8, 0.8},
		{0.1, 0.04}, "2 / 3", "textures/red_button.png", &scale_2_3, NULL, NULL,
		NULL}, &cb->pause.buttons[3]);
	create_button(cb, (t_button){"1/1", {0.275, 0.825}, {0.1, 0.05}, {0.8, 0.8},
		{0.1, 0.04}, "1 / 1", "textures/red_button.png", &scale_1_1, NULL, NULL,
		NULL}, &cb->pause.buttons[4]);
	create_button(cb, (t_button){"3Dcub", {0.375, 0.2}, {0.25, 0.2}, {1, 1.3}, {0,
		-0.3}, "cub3D", "", NULL, NULL, NULL, NULL}, &cb->pause.buttons[5]);
	place_buttons(cb);
}

void	create_pause_screen(t_cub *cb, int action)
{
	int	i;

	if (!cb->pause.image)
		cb->pause.image = mlx_new_image(cb->mlx, WIDTH, HEIGHT);
	mlx_resize_image(cb->pause.image, WIDTH, HEIGHT);
	i = 0;
	while (i < WIDTH * HEIGHT * 4)
	{
		cb->pause.image->pixels[i] = (PAUSE_MENU_COLOR >> 24) & 255;
		cb->pause.image->pixels[i + 1] = (PAUSE_MENU_COLOR >> 16) & 255;
		cb->pause.image->pixels[i + 2] = (PAUSE_MENU_COLOR >> 8) & 255;
		cb->pause.image->pixels[i + 3] = PAUSE_MENU_COLOR & 255;
		i += 4;
	}
	if (action == 1)
		return ;
	cb->pause.image->enabled = cb->flags & PAUSE;
	cb->pause.buttons_count = 6;
	cb->pause.buttons = ft_calloc(sizeof(t_button), cb->pause.buttons_count
			+ 1);
	if (!cb->pause.buttons)
		error(cb, MALLOC_ERROR);
	mlx_image_to_window(cb->mlx, cb->pause.image, 0, 0);
	create_buttons(cb);
}

void	pause_button_press(t_cub *cb)
{
	int	i;

	i = -1;
	while (++i < cb->pause.buttons_count)
		if (is_in_button(cb, cb->pause.buttons[i])
			&& cb->pause.buttons[i].callback)
			cb->pause.buttons[i].callback(cb);
}

void	change_pause_state(t_cub *cb)
{
	int	i;

	i = -1;
	cb->flags ^= PAUSE;
	cb->pause.image->enabled = cb->flags & PAUSE;
	mlx_set_mouse_pos(cb->mlx, WIDTH / 2, HEIGHT / 2);
	while (++i < cb->pause.buttons_count)
	{
		cb->pause.buttons[i].text_img->enabled = cb->flags & PAUSE;
		if (cb->pause.buttons[i].bg)
			cb->pause.buttons[i].bg->enabled = cb->flags & PAUSE;
	}
}
