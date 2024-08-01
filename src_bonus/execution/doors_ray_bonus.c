/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_ray_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:35:28 by bvasseur          #+#    #+#             */
/*   Updated: 2024/07/30 16:17:32 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

static double	cross_product(t_vector p1, t_vector p2, t_vector p3)
{
	return ((p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x));
}

static int	is_point_on_segment(t_vector p, t_vector q, t_vector r)
{
	return (r.x <= ft_fmax(p.x, q.x) && r.x >= ft_fmin(p.x, q.x) && \
			r.y <= ft_fmax(p.y, q.y) && r.y >= ft_fmin(p.y, q.y));
}

static int	is_line_hitting_segment(t_vector v1p1, t_vector v1p2, \
	t_vector v2p1, t_vector v2p2)
{
	double	d1;
	double	d2;
	double	d3;
	double	d4;

	d1 = cross_product(v1p1, v1p2, v2p1);
	d2 = cross_product(v1p1, v1p2, v2p2);
	d3 = cross_product(v2p1, v2p2, v1p1);
	d4 = cross_product(v2p1, v2p2, v1p2);
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

static int	ray_hit_door(t_cub *cb, t_raycaster *ray, int i)
{
	return (cb->doors[i].pos.x == ray->map_x && cb->doors[i].pos.y == \
		ray->map_y && ((cb->doors[i].side == 0 && \
		is_line_hitting_segment(cb->player.pos, set_vector(cb->player.pos.x \
		+ ray->raydir.x, cb->player.pos.y + ray->raydir.y), \
		set_vector(cb->doors[i].pos.x + cb->doors[i].in_percentage, \
		cb->doors[i].pos.y), set_vector(cb->doors[i].pos.x + \
		cb->doors[i].in_percentage, cb->doors[i].pos.y + 1 * \
		cb->doors[i].timer))) || (cb->doors[i].side == 1 && \
		is_line_hitting_segment(cb->player.pos, set_vector(cb->player.pos.x + \
		ray->raydir.x, cb->player.pos.y + ray->raydir.y), \
		set_vector(cb->doors[i].pos.x, cb->doors[i].pos.y + \
		cb->doors[i].in_percentage), set_vector(cb->doors[i].pos.x + 1 * \
		cb->doors[i].timer, cb->doors[i].pos.y + \
		cb->doors[i].in_percentage)))));
}

void	raycaster_door(t_cub *cb, t_raycaster *ray)
{
	int	i;

	i = -1;
	while (++i < cb->nb_of_doors)
	{
		if (ray_hit_door(cb, ray, i))
		{
			ray->hit = 1;
			ray->is_door = 1;
			ray->hit_door = cb->doors[i];
			if (cb->doors[i].side == 0 && cb->player.pos.x < cb->doors[i].pos.x)
				ray->side_dist.x += cb->doors[i].in_percentage;
			else if (cb->doors[i].side == 0 && cb->player.pos.x > \
				cb->doors[i].pos.x)
				ray->side_dist.x += 1 - cb->doors[i].in_percentage;
			else if (cb->doors[i].side == 1 && cb->player.pos.y < \
				cb->doors[i].pos.y)
				ray->side_dist.y += cb->doors[i].in_percentage;
			else if (cb->doors[i].side == 1 && cb->player.pos.y > \
				cb->doors[i].pos.y)
				ray->side_dist.y += 1 - cb->doors->in_percentage;
			break ;
		}
	}
}
