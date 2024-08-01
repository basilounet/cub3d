/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_raycaster_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:32:32 by bvasseur          #+#    #+#             */
/*   Updated: 2024/07/30 16:38:31 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	sort_entities(t_cub *cb, t_entity *entities, int nb)
{
	t_entity	entity;
	int			i;
	int			j;

	i = -1;
	while (++i < nb)
	{
		entities[i].player_dist = vector_length(set_vector(cb->player.pos.x - \
		entities[i].pos.x, cb->player.pos.y - entities[i].pos.y));
		if (cb->entities[i].type == ENEMY)
			entities[i].texture = cb->map.enemy_back_texture;
		if (cb->entities[i].type == ENEMY && is_player_in_vision(cb->player, \
			entities[i], 180))
			entities[i].texture = cb->map.enemy_texture;
	}
	i = -1;
	while (++i < nb)
	{
		j = i + 1;
		entity = entities[i];
		while (--j > 0 && entities[j - 1].player_dist < entity.player_dist)
			entities[j] = entities[j - 1];
		entities[j] = entity;
	}
	i = 0;
}

static int	get_entity_color(t_cub *cb, t_raycaster_entity ray, \
	mlx_texture_t *txt)
{
	double	fog_percentage;
	double	light_percentage;

	light_percentage = 0;
	if (cb->flags & LIGHT_ON)
		ray.y += cb->player.pitch + (ft_fclamp(cos(cb->player.jiggle), \
		-.7, .7) * JIGGLE_FORCE / ray.entity.player_dist);
	if (cb->flags & LIGHT_ON && ft_abs(ray.stripe - WIDTH / 2) <= HEIGHT * \
		LIGHT_SIZE && ft_abs(ray.y - HEIGHT / 2) <= HEIGHT * LIGHT_SIZE)
		light_percentage = get_light_percentage(ray.stripe, ray.y);
	fog_percentage = ft_fclamp(ray.entity.player_dist / (FOG_DISTANCE + \
		light_percentage * LIGHT_DISTANCE_MULTIPLIER * FOG_DISTANCE), 0, 1);
	return ((int)((1 - fog_percentage) * txt->pixels[txt->width * ray.texY * 4 \
		+ ft_abs(ray.texX - txt->width + 1) * 4] + fog_percentage * (FOG >> 24 \
		& 255)) << 24 | (int)((1 - fog_percentage) * txt->pixels[txt->width * \
		ray.texY * 4 + ft_abs(ray.texX - txt->width + 1) * 4 + 1] + \
		fog_percentage * (FOG >> 16 & 255)) << 16 | (int)((1 - fog_percentage) \
		* txt->pixels[txt->width * ray.texY * 4 + ft_abs(ray.texX - txt->width \
		+ 1) * 4 + 2] + fog_percentage * (FOG >> 8 & 255)) << 8 | \
		txt->pixels[txt->width * ray.texY * 4 + ft_abs(ray.texX - txt->width + \
		1) * 4 + 3]);
}

static void	entities_raycaster_set_var(t_player pl, \
	t_raycaster_entity *ray)
{
	ray->spriteX = ray->entity.pos.x - pl.pos.x;
	ray->spriteY = ray->entity.pos.y - pl.pos.y;
	ray->invDet = 1.0 / (pl.plane.x * pl.facing.y - \
		pl.facing.x * pl.plane.y);
	ray->transformX = ray->invDet * (pl.facing.y * ray->spriteX - pl.facing.x \
		* ray->spriteY);
	ray->transformY = ray->invDet * (-pl.plane.y * ray->spriteX + pl.plane.x \
		* ray->spriteY);
	ray->spriteScreenX = (int)((WIDTH / 2) * (1 + ray->transformX / \
		ray->transformY));
	ray->spriteHeight = ft_abs((int)(HEIGHT / (ray->transformY)));
	ray->drawStartY = -ray->spriteHeight / 2 + HEIGHT / 2;
	ray->drawEndY = ray->spriteHeight / 2 + HEIGHT / 2;
	ray->spriteWidth = ft_abs((int)(HEIGHT / (ray->transformY)));
	ray->drawStartX = -ray->spriteWidth / 2 + ray->spriteScreenX;
	if (ray->drawStartX < 0)
		ray->drawStartX = 0;
	ray->drawEndX = ray->spriteWidth / 2 + ray->spriteScreenX;
	if (ray->drawEndX >= WIDTH)
		ray->drawEndX = WIDTH - 1;
	ray->stripe = ray->drawStartX;
}

static void	draw_stripe(t_cub *cb, t_raycaster_entity *ray)
{
	uint32_t	color;
	int			d;

	ray->texX = (int)(256 * (ray->stripe - (-ray->spriteWidth / 2 + \
		ray->spriteScreenX)) * ray->entity.texture->width / \
		ray->spriteWidth) / 256;
	if (ray->transformY > 0 && ray->stripe > 0 && ray->stripe < WIDTH && \
		ray->transformY < cb->z_buffer[ray->stripe])
	{
		ray->y = ray->drawStartY;
		while (ray->y < ray->drawEndY)
		{
			d = (ray->y) * 256 - HEIGHT * 128 + ray->spriteHeight * 128;
			ray->texY = ((d * ray->entity.texture->height) / \
				ray->spriteHeight) / 256;
			color = get_entity_color(cb, *ray, ray->entity.texture);
			if (color & 0xFF)
				try_put_pixel(cb->image, ray->stripe, ray->y + \
					cb->player.pitch + (ft_fclamp(cos(cb->player.jiggle), -.7, \
					.7) * JIGGLE_FORCE / ray->entity.player_dist), color);
			ray->y++;
		}
	}
}

void	raycaster_entities(t_cub *cb, t_player pl, t_entity *entities, int nb)
{
	t_raycaster_entity	ray;
	int					i;

	ray = (t_raycaster_entity){0};
	sort_entities(cb, entities, nb);
	i = -1;
	while (++i < nb)
	{
		ray.entity = entities[i];
		entities_raycaster_set_var(pl, &ray);
		while (ray.stripe < ray.drawEndX)
		{
			draw_stripe(cb, &ray);
			ray.stripe++;
		}
	}
}
