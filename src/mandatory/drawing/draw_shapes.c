/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:24:38 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/27 11:24:41 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_rectangle(mlx_image_t *img, t_vector pos, t_vector size, int color)
{
	uint32_t	x;
	uint32_t	y;

	y = pos.y;
	while (y < pos.y + size.y)
	{
		x = pos.x;
		while (x < pos.x + size.x)
		{
			if (x >= 0 && x < img->width && y >= 0 && y < img->height)
				mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}
