/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_callback_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:39:38 by bvasseur          #+#    #+#             */
/*   Updated: 2024/07/13 14:20:40 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	mm_width_slider(t_cub *cb, t_slider *slider)
{
	t_slider	*mm_pos_x;

	mm_pos_x = &cb->pause.sliders[12];
	update_slider_values(cb, slider);
	change_map_state(cb, 1, slider->value, -1);
	if ((cb->flags & FULL_MAP) == 0)
		cb->minimap.width = slider->value;
	if ((cb->flags & FULL_MAP) == 0)
		mlx_resize_image(cb->minimap.image, cb->minimap.width, \
			cb->minimap.height);
	mm_pos_x->max = WIDTH - 20 - slider->value + 2;
	mm_pos_x->percentage = (mm_pos_x->value - mm_pos_x->min) / \
		(double)(mm_pos_x->max - mm_pos_x->min);
	mm_pos_x->button.pos.x = mm_pos_x->range.x + (mm_pos_x->range.y
			- mm_pos_x->range.x) * mm_pos_x->percentage + \
			mm_pos_x->button_offset.x;
	mm_pos_x->button.bg->instances[0].x = mm_pos_x->button.pos.x * WIDTH;
}

void	mm_height_slider(t_cub *cb, t_slider *slider)
{
	t_slider	*mm_pos_y;

	mm_pos_y = &cb->pause.sliders[13];
	update_slider_values(cb, slider);
	change_map_state(cb, 1, -1, slider->value);
	if ((cb->flags & FULL_MAP) == 0)
		cb->minimap.height = slider->value;
	if ((cb->flags & FULL_MAP) == 0)
		mlx_resize_image(cb->minimap.image, cb->minimap.width, \
			cb->minimap.height);
	mm_pos_y->max = HEIGHT - 20 - slider->value + 2;
	mm_pos_y->percentage = (mm_pos_y->value - mm_pos_y->min) / \
		(double)(mm_pos_y->max - mm_pos_y->min);
	mm_pos_y->button.pos.x = mm_pos_y->range.x + (mm_pos_y->range.y
			- mm_pos_y->range.x) * mm_pos_y->percentage + \
			mm_pos_y->button_offset.x;
	mm_pos_y->button.bg->instances[0].x = mm_pos_y->button.pos.x * WIDTH;
}

void	mm_zoom_slider(t_cub *cb, t_slider *slider)
{
	update_slider_values(cb, slider);
	cb->minimap.square_size = (double)slider->value;
}

void	mm_pos_x_slider(t_cub *cb, t_slider *slider)
{
	t_slider	*mm_width;

	mm_width = &cb->pause.sliders[3];
	update_slider_values(cb, slider);
	mm_width->max = WIDTH - 20 - slider->value + 1;
	slider->max = WIDTH - 20 - mm_width->value;
	mm_width->percentage = (mm_width->value - mm_width->min) / \
			(double)(mm_width->max - mm_width->min);
	mm_width->button.pos.x = mm_width->range.x + (mm_width->range.y
			- mm_width->range.x) * mm_width->percentage + \
			mm_width->button_offset.x;
	mm_width->button.bg->instances[0].x = mm_width->button.pos.x * WIDTH;
	if ((cb->flags & FULL_MAP) == 0)
		cb->minimap.image->instances[0].x = slider->value;
}

void	mm_pos_y_slider(t_cub *cb, t_slider *slider)
{
	t_slider	*mm_height;

	mm_height = &cb->pause.sliders[4];
	update_slider_values(cb, slider);
	mm_height->max = HEIGHT - 20 - slider->value + 1;
	slider->max = HEIGHT - 20 - mm_height->value;
	mm_height->percentage = (mm_height->value
			- mm_height->min) / (double)(mm_height->max - mm_height->min);
	mm_height->button.pos.x = mm_height->range.x + (mm_height->range.y
			- mm_height->range.x) * mm_height->percentage + \
			mm_height->button_offset.x;
	mm_height->button.bg->instances[0].x = mm_height->button.pos.x * WIDTH;
	if ((cb->flags & FULL_MAP) == 0)
		cb->minimap.image->instances[0].y = slider->value;
}
