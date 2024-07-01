/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 21:01:59 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/27 11:32:23 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

static void	bresenham_values_init(t_bresenham *br, t_vector p0, t_vector p1)
{
	br->dx = ft_abs(p1.x - p0.x);
	br->dy = ft_abs(p1.y - p0.y);
	if (p0.x < p1.x)
		br->sx = 1;
	else
		br->sx = -1;
	if (p0.y < p1.y)
		br->sy = 1;
	else
		br->sy = -1;
	br->err = br->dx - br->dy;
}

void	draw_line(mlx_image_t *img, t_vector p0, t_vector p1, int color)
{
	t_bresenham	br;

	bresenham_values_init(&br, p0, p1);
	while (1)
	{
		try_put_pixel(img, p0.x, p0.y, color);
		if (p0.x == p1.x && p0.y == p1.y)
			break ;
		br.e2 = 2 * br.err;
		if (br.e2 > -br.dy)
		{
			br.err -= br.dy;
			p0.x += br.sx;
		}
		if (br.e2 < br.dx)
		{
			br.err += br.dx;
			p0.y += br.sy;
		}
	}
}
