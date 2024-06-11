/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 21:01:59 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/11 16:25:02 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// static void	x_cartesian_equation(mlx_image_t *img, t_ce ce, int color)
// {
// 	t_vector	tmp;

// 	if (ce.pos1.x > ce.pos2.x)
// 	{
// 		tmp = ce.pos2;
// 		ce.pos2 = ce.pos1;
// 		ce.pos1 = tmp;
// 	}
// 	ce.c = -ce.dy * ce.pos1.x + ce.dx * ce.pos1.y;
// 	ce.x = ce.pos1.x;
// 	while (ce.x <= ce.pos2.x)
// 	{
// 		ce.y = (-ce.dy * ce.x - ce.c) / -ce.dx;
// 		try_put_pixel(img, ce.x, ce.y, color);
// 		ce.x++;
// 	}
// }

// static void	y_cartesian_equation(mlx_image_t *img, t_ce ce, int color)
// {
// 	t_vector	tmp;

// 	if (ce.pos1.y > ce.pos2.y)
// 	{
// 		tmp = ce.pos2;
// 		ce.pos2 = ce.pos1;
// 		ce.pos1 = tmp;
// 	}
// 	ce.c = -ce.dy * ce.pos1.x + ce.dx * ce.pos1.y;
// 	ce.y = ce.pos1.y;
// 	while (ce.y <= ce.pos2.y)
// 	{
// 		ce.x = (ce.dx * ce.y - ce.c) / ce.dy;
// 		try_put_pixel(img, ce.x, ce.y, color);
// 		ce.y++;
// 	}
// }

// void	draw_line(mlx_image_t *img, t_vector pos1, t_vector pos2, int color)
// {
// 	t_ce	ce;

// 	ce.pos1 = pos1;
// 	ce.pos2 = pos2;
// 	ce.dx = ce.pos1.x - ce.pos2.x;
// 	ce.dy = ce.pos1.y - ce.pos2.y;
// 	printf("dx : %d, dy %d\n", ce.dx, ce.dy);
// 	if (ce.dx == 0 && ce.dy == 0)
// 		return ;
// 	if (ft_abs(ce.dx) > ft_abs(ce.dy))
// 		x_cartesian_equation(img, ce, color);
// 	else
// 		y_cartesian_equation(img, ce, color);
// }

void	draw_line(mlx_image_t *img, t_vector p0, t_vector p1, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = ft_abs(p1.x - p0.x);
	dy = ft_abs(p1.y - p0.y);
	sx = (p0.x < p1.x) ? 1 : -1;
	sy = (p0.y < p1.y) ? 1 : -1;
	err = dx - dy;
	printf("dx : %d, dy %d\n", dx, dy);
	while (1)
	{
		try_put_pixel(img, p0.x, p0.y, color);
		if (p0.x == p1.x && p0.y == p1.y)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			p0.x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			p0.y += sy;
		}
	}
}
