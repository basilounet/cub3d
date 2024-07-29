/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:59:53 by bvasseur          #+#    #+#             */
/*   Updated: 2024/07/28 18:33:58 by bvasseur         ###   ########.fr       */
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
			|| cb->map.map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

static void	draw_screen(t_cub *cb, t_raycaster *ray, int x)
{
	mlx_texture_t	*txt;

	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
	if (ray->side == 0)
		ray->wall_x = cb->player.pos.y + ray->perp_wall_dist * ray->raydir.y;
	else
		ray->wall_x = cb->player.pos.x + ray->perp_wall_dist * ray->raydir.x;
	ray->wall_x -= floor(ray->wall_x);
	txt = get_wall_texture(cb, ray);
	ray->tex_x = (int)(ray->wall_x * (double)txt->width);
	if ((ray->side == 0 && ray->raydir.x > 0) || (ray->side == 1
			&& ray->raydir.y < 0))
		ray->tex_x = txt->width - ray->tex_x - 1;
	ray->step = 1.0 * txt->height / ray->line_height;
	ray->tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * \
	ray->step;
	print_pixel(cb, ray, x, txt);
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
			ray.perp_wall_dist = (ray.side_dist.x - ray.delta_dist.x);
		else
			ray.perp_wall_dist = (ray.side_dist.y - ray.delta_dist.y);
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
