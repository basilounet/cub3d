/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:59:53 by bvasseur          #+#    #+#             */
/*   Updated: 2024/07/29 13:41:00 by bvasseur         ###   ########.fr       */
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

double cross_product(t_vector p1, t_vector p2, t_vector p3) {
    // Calculate the cross product of vectors p1p2 and p1p3
    return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

int	is_point_on_segment(t_vector p, t_vector q, t_vector r) {
    // Check if point r is on segment pq
    return r.x <= fmax(p.x, q.x) && r.x >= fmin(p.x, q.x) &&
           r.y <= fmax(p.y, q.y) && r.y >= fmin(p.y, q.y);
}

int	is_line_hitting_segment(t_vector v1p1, t_vector v1p2, t_vector v2p1, t_vector v2p2)
{
    double d1 = cross_product(v1p1, v1p2, v2p1);
    double d2 = cross_product(v1p1, v1p2, v2p2);
    double d3 = cross_product(v2p1, v2p2, v1p1);
    double d4 = cross_product(v2p1, v2p2, v1p2);

    if ((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0))
        return (1);
    if (d1 == 0 && is_point_on_segment(v1p1, v1p2, v2p1))
		return (1);
    if (d2 == 0 && is_point_on_segment(v1p1, v1p2, v2p2))
		return (1);
    if (d3 == 0 && is_point_on_segment(v2p1, v2p2, v1p1))
		return (1);
    if (d4 == 0 && is_point_on_segment(v2p1, v2p2, v1p2))
		return (1);
    return (0);
}

static void dda(t_cub *cb, t_raycaster *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		} else {
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0 || ray->map_y >= cb->map.height || ray->map_x < 0 ||
			ray->map_x >= (int)ft_strlen(cb->map.map[ray->map_y]) || 
			cb->map.map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
		else if (cb->map.map[ray->map_y][ray->map_x] == 'D')
		{
			// Check if the ray hits a door
			for (int i = 0; i < cb->nb_of_doors; i++)
			{
				if (cb->doors[i].pos.x == ray->map_x && cb->doors[i].pos.y == ray->map_y)
				{
					// printf("side : %d\n", cb->doors[i].side);
					if ((cb->doors[i].side == 0 && is_line_hitting_segment(cb->player.pos, set_vector(cb->player.pos.x + ray->raydir.x, cb->player.pos.y + ray->raydir.y), \
						set_vector(cb->doors[i].pos.x + cb->doors[i].in_percentage, cb->doors[i].pos.y), set_vector(cb->doors[i].pos.x + cb->doors[i].in_percentage, cb->doors[i].pos.y + 1))) \
						|| (cb->doors[i].side == 1 && is_line_hitting_segment(cb->player.pos, set_vector(cb->player.pos.x + ray->raydir.x, cb->player.pos.y + ray->raydir.y), \
						set_vector(cb->doors[i].pos.x, cb->doors[i].pos.y + cb->doors[i].in_percentage), set_vector(cb->doors[i].pos.x + 1, cb->doors[i].pos.y + cb->doors[i].in_percentage))))
					{
						ray->hit = 1;
						ray->is_door = 1;
						ray->hit_door = cb->doors[i];
						if (cb->doors[i].side == 0)
							// ray->side_dist = set_vector(ray->side_dist.x + cb->doors[i].in_percentage, );
							ray->side_dist.x += cb->doors[i].in_percentage;
						else
							ray->side_dist.y += cb->doors[i].in_percentage;
						break;
					}
				}
			}
		}
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

double	get_light_percentage(int x, int y)
{
	double dx;
	double dy;
	double percentage;

	dx = x - WIDTH / 2;
	dy = y - HEIGHT / 2;
	percentage = 1.0 - (sqrt(dx * dx + dy * dy) / (LIGHT_SIZE * HEIGHT));
	return (ft_fclamp(percentage, 0.0, 1.0));
}

int	get_color(t_cub *cb, t_raycaster *ray, mlx_texture_t *txt)
{
	double	fog_percentage;
	double	light_percentage;

	light_percentage = 0;
	if (cb->flags & LIGHT_ON && ft_abs(ray->x - WIDTH / 2) <= HEIGHT * \
		LIGHT_SIZE && ft_abs(ray->y - HEIGHT / 2) <= HEIGHT * LIGHT_SIZE)
		light_percentage = get_light_percentage(ray->x, ray->y);
	fog_percentage = ft_fclamp(ray->perp_wall_dist / (FOG_DISTANCE + \
		light_percentage * LIGHT_DISTANCE_MULTIPLIER * FOG_DISTANCE), 0, 1);
	return ((int)((1 - fog_percentage) * txt->pixels[txt->width * ray->tex_y * \
		4 + ft_abs(ray->tex_x - txt->width + 1) * 4] + fog_percentage * (FOG >> \
		24 & 255)) << 24 | (int)((1 - fog_percentage) * txt->pixels[txt->width * \
		ray->tex_y * 4 + ft_abs(ray->tex_x - txt->width + 1) * 4 + 1] + \
		fog_percentage * (FOG >> 16 & 255)) << 16 | (int)((1 - fog_percentage) * \
		txt->pixels[txt->width * ray->tex_y * 4 + ft_abs(ray->tex_x - \
		txt->width + 1) * 4 + 2] + fog_percentage * (FOG >> 8 & 255)) << 8 | \
		txt->pixels[txt->width * ray->tex_y * 4 + ft_abs(ray->tex_x - txt->width \
		+ 1) * 4 + 3]);
}

static void	draw_screen(t_cub *cb, t_raycaster *ray)
{
	mlx_texture_t	*txt;

	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2 + cb->player.pitch + (ft_fclamp(cos(cb->player.jiggle), -.7, .7) * JIGGLE_FORCE / ray->perp_wall_dist);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2 + cb->player.pitch + (ft_fclamp(cos(cb->player.jiggle), -.7, .7) * JIGGLE_FORCE / ray->perp_wall_dist);
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
	ray->texPos = (ray->draw_start - HEIGHT / 2 - cb->player.pitch - (ft_fclamp(cos(cb->player.jiggle), -.7, .7) * JIGGLE_FORCE / ray->perp_wall_dist) + ray->line_height / 2) * ray->step;
	ray->y = ray->draw_start;
	while (ray->y < ray->draw_end)
	{
		ray->tex_y = (int)ray->texPos & (txt->height - 1);
		ray->texPos += ray->step;
		try_put_pixel(cb->image, ray->x, ray->y + 1, get_color(cb, ray, txt));
		ray->y++;
	}
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
	draw_rectangle(cb->image, set_vector(0, 0), set_vector(WIDTH, HEIGHT / 2 + cb->player.pitch),
		cb->map.ceiling_color);
	draw_rectangle(cb->image, set_vector(0, HEIGHT / 2 + cb->player.pitch), set_vector(WIDTH,
			HEIGHT / 2  - cb->player.pitch), cb->map.floor_color);
	raycaster_loop(cb, cb->player);
	raycaster_entities(cb, cb->player, cb->entities, cb->nb_of_entities);
}