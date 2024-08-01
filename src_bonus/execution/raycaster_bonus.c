/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:59:53 by bvasseur          #+#    #+#             */
/*   Updated: 2024/07/30 16:11:15 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

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
		if (ray->map_y < 0 || ray->map_y >= cb->map.height || ray->map_x < 0 \
		|| ray->map_x >= (int)ft_strlen(cb->map.map[ray->map_y]) || \
			cb->map.map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
		else if (cb->map.map[ray->map_y][ray->map_x] == 'D')
			raycaster_door(cb, ray);
	}
}

mlx_texture_t	*get_wall_texture(t_cub *cb, t_raycaster *ray)
{
	if (cb->player.pos.y < 0 || cb->player.pos.y >= cb->map.height
		|| cb->player.pos.x < 0
		|| cb->player.pos.x >= ft_strlen(cb->map.map[(int)cb->player.pos.y])
		|| (cb->map.map[(int)cb->player.pos.y][(int)cb->player.pos.x] != '0' && \
		cb->map.map[(int)floor(cb->player.pos.y)][(int)floor(cb->player.pos.x)] \
		!= 'D' && \
		cb->map.map[(int)floor(cb->player.pos.y)][(int)floor(cb->player.pos.x)] \
		!= 'M' && \
		cb->map.map[(int)floor(cb->player.pos.y)][(int)floor(cb->player.pos.x)] \
		!= 'I'))
		return (cb->map.bozo_texture);
	if (ray->is_door)
		return (cb->map.door_texture);
	if (ray->side == 0 && ray->raydir.x > 0)
		return (cb->map.west_texture);
	if (ray->side == 0 && ray->raydir.x < 0)
		return (cb->map.east_texture);
	if (ray->side == 1 && ray->raydir.y < 0)
		return (cb->map.south_texture);
	if (ray->side == 1 && ray->raydir.y > 0)
		return (cb->map.north_texture);
	return (cb->map.bozo_texture);
}

static void	raycaster_loop(t_cub *cb, t_player pl)
{
	t_raycaster	ray;
	int			x;

	x = 0;
	while (x < WIDTH)
	{
		ray = (t_raycaster){0};
		ray.x = x;
		ray.camera.x = 2 * ray.x / (double)WIDTH - 1;
		ray.raydir.x = pl.facing.x + pl.plane.x * ray.camera.x;
		ray.raydir.y = pl.facing.y + pl.plane.y * ray.camera.x;
		raycaster_set_var(cb->player, &ray);
		dda(cb, &ray);
		if (ray.side == 0)
			ray.perp_wall_dist = (ray.side_dist.x - ray.delta_dist.x);
		else
			ray.perp_wall_dist = (ray.side_dist.y - ray.delta_dist.y);
		draw_screen(cb, &ray);
		cb->z_buffer[x] = ray.perp_wall_dist;
		x++;
	}
}

void	raycaster(t_cub *cb)
{
	draw_rectangle(cb->image, set_vector(0, 0), set_vector(WIDTH, HEIGHT / 2 + \
	cb->player.pitch), cb->map.ceiling_color);
	draw_rectangle(cb->image, set_vector(0, HEIGHT / 2 + cb->player.pitch), \
		set_vector(WIDTH, HEIGHT / 2 - cb->player.pitch), cb->map.floor_color);
	raycaster_loop(cb, cb->player);
	raycaster_entities(cb, cb->player, cb->entities, cb->nb_of_entities);
}
