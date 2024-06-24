/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shape.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:24:38 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/24 18:18:48 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	try_put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, int color)
{
	if (x < 0 || x > img->width || y < 0 || y > img->height)
		return ;
	mlx_put_pixel(img, x, y, color);
}

void	draw_triangle(mlx_image_t *img, t_vector pos, t_vector facing,
		int color)
{
	double		base_length;
	double		magnitude;
	t_vector	direction;
	t_vector	points[3];

	base_length = (MINIMAP_SQUARE_SIZE - MINIMAP_SQUARE_SIZE / 3) / 2;
	magnitude = sqrt(facing.x * facing.x + facing.y * facing.y);
	direction = set_vector(facing.x / magnitude, facing.y / magnitude);
	points[0] = set_vector(pos.x + direction.x * MINIMAP_SQUARE_SIZE / 2, pos.y
			+ direction.y * MINIMAP_SQUARE_SIZE / 2);
	points[1] = set_vector(pos.x - direction.y * base_length / 2, pos.y
			+ direction.x * base_length / 2);
	points[2] = set_vector(pos.x + direction.y * base_length / 2, pos.y
			- direction.x * base_length / 2);
	draw_line(img, set_vector((int)round(points[0].x), (int)round(points[0].y)),
		set_vector((int)round(points[1].x), (int)round(points[1].y)), color);
	draw_line(img, set_vector((int)round(points[1].x), (int)round(points[1].y)),
		set_vector((int)round(points[2].x), (int)round(points[2].y)), color);
	draw_line(img, set_vector((int)round(points[2].x), (int)round(points[2].y)),
		set_vector((int)round(points[0].x), (int)round(points[0].y)), color);
}

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
			if ((x >= 0 && x < img->width && y >= 0 && y < img->height)
				&& ((x < pos.x + 5 || x > pos.x + size.x - 5) || (y < pos.y + 5
						|| y > pos.y + size.y - 5)))
				mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}
