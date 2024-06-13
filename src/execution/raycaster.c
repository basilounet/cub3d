/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:59:53 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/13 13:18:10 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	raycaster_set_var(t_player pl, t_raycaster *ray)
{
	ray->map_x = (int)pl.pos.x;
	ray->map_y = (int)pl.pos.y;
	ray->delta_dist.x = fabs(1 / ray->raydir.x);
	ray->delta_dist.y = fabs(1 / ray->raydir.y);
	if (ray->raydir.x < 0)
	{
		ray->step_x = -1;
		ray->side_dist.x = (pl.pos.x - ray->map_x) * ray->delta_dist.x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist.x = (ray->map_x + 1.0 - pl.pos.x) * ray->delta_dist.x;
	}
	if (ray->raydir.y < 0)
	{
		ray->step_y = -1;
		ray->side_dist.y = (pl.pos.y - ray->map_y) * ray->delta_dist.y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist.y = (ray->map_y + 1.0 - pl.pos.y) * ray->delta_dist.y;
	}
}

static void	dda(t_cub *cb, t_raycaster *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0 || ray->map_y >= cb->map.height
			|| cb->map.map[ray->map_y][ray->map_x] != '0')
			ray->hit = 1;
	}
}

static void	draw_screen(t_cub *cb, t_raycaster *ray, int x)
{
	int	color;

	ray->lineHeight = (int)(HEIGHT / ray->perpWallDist);
	ray->drawStart = -ray->lineHeight / 2 + HEIGHT / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->lineHeight / 2 + HEIGHT / 2;
	if (ray->drawEnd >= HEIGHT)
		ray->drawEnd = HEIGHT - 1;
	color = 0xFFFF00FF;
	if (ray->side == 1)
		color = color / 2;
	draw_line(cb->image, set_vector(x, ray->drawStart), set_vector(x,
			ray->drawEnd), color);
}

static void	raycaster_loop(t_cub *cb, t_player pl)
{
	t_raycaster	ray;
	int			x;

	x = 0;
	while (x < WIDTH)
	{
		ray = (t_raycaster){0};
		ray.camera.x = 2 * x / (double)WIDTH - 1;
		ray.raydir.x = pl.facing.x + pl.plane.x * ray.camera.x;
		ray.raydir.y = pl.facing.y + pl.plane.y * ray.camera.x;
		raycaster_set_var(cb->player, &ray);
		dda(cb, &ray);
		if (ray.side == 0)
			ray.perpWallDist = (ray.side_dist.x - ray.delta_dist.x);
		else
			ray.perpWallDist = (ray.side_dist.y - ray.delta_dist.y);
		if (ray.perpWallDist <= 0.1f)
			ray.perpWallDist = 1;
		draw_screen(cb, &ray, x);
		x++;
	}
}

void	raycaster(t_cub *cb)
{
	draw_rectangle(cb->image, set_vector(0, 0), set_vector(WIDTH, HEIGHT / 2),
		cb->map.ceiling_color);
	draw_rectangle(cb->image, set_vector(0, HEIGHT / 2), set_vector(WIDTH,
			HEIGHT / 2), cb->map.floor_color);
	raycaster_loop(cb, cb->player);
}
