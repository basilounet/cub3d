/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shape.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:24:38 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/07 20:32:27 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_rectangle(mlx_image_t *img, t_vector pos, t_vector size, int color)
{
	uint32_t	x;
	uint32_t	y;

    printf("case pos [%f, %f]\n", pos.x, pos.y);
	y = pos.y;
	while (y < pos.y + size.y)
	{
		x = pos.x;
		while (x < pos.x + size.x)
		{
			if (x > 0 && x < img->width && y > 0 && y <= img->height)
				mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}
void	draw_empty_rectangle(mlx_image_t *img, t_vector pos, t_vector size,
		int color)
{
	uint32_t	x;
	uint32_t	y;

	y = pos.y;
	while (y < pos.y + size.y)
	{
		x = pos.x;
		while (x < pos.x + size.x)
		{
			if ((x > 0 && x < img->width && y > 0 && y < img->height)
				&& ((x < pos.x + 5 || x > pos.x + size.x - 5) || (y < pos.y + 5
					|| y > pos.y + size.y - 5)))
				mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}
