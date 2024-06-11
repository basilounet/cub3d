/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:59:53 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/11 16:38:18 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	raycaster_loop(t_cub *cb, t_player pl)
{
	t_raycaster	ray;
	int			lineHeight;
	int			drawStart;
	int			drawEnd;
		int color;

	for (int x = 0; x < WIDTH; x++)
	{
		// calculate ray position and direction
		ray = (t_raycaster){0};
		ray.camera.x = 2 * x / (double)WIDTH - 1;
			// x-coordinate in camera space
		ray.raydir.x = pl.facing.x + pl.plane.x * ray.camera.x;
		ray.raydir.y = pl.facing.y + pl.plane.y * ray.camera.x;
		// which box of the map we're in
		ray.map_x = (int)pl.pos.x;
		ray.map_y = (int)pl.pos.y;
		// length of ray from one x or y-side to next x or y-side
		ray.delta_dist.x = fabs(1 / ray.raydir.x);
		ray.delta_dist.y = fabs(1 / ray.raydir.y);
		if (ray.raydir.x < 0)
		{
			ray.step_x = -1;
			ray.side_dist.x = (pl.pos.x - ray.map_x) * ray.delta_dist.x;
		}
		else
		{
			ray.step_x = 1;
			ray.side_dist.x = (ray.map_x + 1.0 - pl.pos.x) * ray.delta_dist.x;
		}
		if (ray.raydir.y < 0)
		{
			ray.step_y = -1;
			ray.side_dist.y = (pl.pos.y - ray.map_y) * ray.delta_dist.y;
		}
		else
		{
			ray.step_y = 1;
			ray.side_dist.y = (ray.map_y + 1.0 - pl.pos.y) * ray.delta_dist.y;
		}
		// perform DDA
		while (ray.hit == 0)
		{
			if (ray.side_dist.x < ray.side_dist.y)
			{
				ray.side_dist.x += ray.delta_dist.x;
				ray.map_x += ray.step_x;
				ray.side = 0;
			}
			else
			{
				ray.side_dist.y += ray.delta_dist.y;
				ray.map_y += ray.step_y;
				ray.side = 1;
			}
			if (cb->map.map[ray.map_y][ray.map_x] != '0')
				ray.hit = 1;
		}
		// Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
		if (ray.side == 0)
			ray.perpWallDist = (ray.side_dist.x - ray.delta_dist.x);
		else
			ray.perpWallDist = (ray.side_dist.y - ray.delta_dist.y);
		if (ray.perpWallDist <= 0.1f)
			ray.perpWallDist = 1;
		// Calculate height of line to draw on screen
		lineHeight = (int)(HEIGHT / ray.perpWallDist);
		// calculate lowest and highest pixel to fill in current stripe
		drawStart = -lineHeight / 2 + HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + HEIGHT / 2;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;
		color = 0xFFFF00FF;
		// give x and y sides different brightness
		if (ray.side == 1)
			color = color / 2;
		// draw the pixels of the stripe as a vertical line
		printf("perpwall dist : %f\n", ray.perpWallDist);
		draw_line(cb->image, set_vector(x, drawStart), set_vector(x, drawEnd),
			color);
	}
}

void	raycaster(t_cub *cb)
{
	double	plane_length;

	cb->player.fov = 66;
	plane_length = tan(cb->player.fov / 2 * (M_PI / 180));
	cb->player.plane = set_vector(plane_length * -cb->player.facing.y,
			plane_length * cb->player.plane.x);
	// printf("fov : %d, plane_length : %f plane : [%f, %f]\n", cb->player.fov,
	// plane_length, cb->player.plane.x, cb->player.plane.y);
	draw_rectangle(cb->image, set_vector(0, 0), set_vector(WIDTH, HEIGHT / 2),
		cb->map.ceiling_color);
	draw_rectangle(cb->image, set_vector(0, HEIGHT / 2), set_vector(WIDTH,
			HEIGHT / 2), cb->map.floor_color);
	raycaster_loop(cb, cb->player);
}
