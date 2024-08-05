/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_raycaster_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:32:32 by bvasseur          #+#    #+#             */
/*   Updated: 2024/07/31 16:13:24 by amolbert         ###   ########.fr       */
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
	int		color;

	light_percentage = 0;
	if (cb->flags & LIGHT_ON)
		ray.y += cb->player.pitch + (ft_fclamp(cos(cb->player.jiggle), \
		-.7, .7) * JIGGLE_FORCE / ray.entity.player_dist);
	if (cb->flags & LIGHT_ON && ft_abs(ray.stripe - WIDTH / 2) <= HEIGHT * \
		LIGHT_SIZE && ft_abs(ray.y - HEIGHT / 2) <= HEIGHT * LIGHT_SIZE)
		light_percentage = get_light_percentage(ray.stripe, ray.y);
	fog_percentage = ft_fclamp(ray.entity.player_dist / (FOG_DISTANCE + \
		light_percentage * LIGHT_DISTANCE_MULTIPLIER * FOG_DISTANCE), 0, 1);
	color = (int)((1 - fog_percentage) * txt->pixels[txt->width * ray.tex_y * 4 \
		+ ft_abs(ray.tex_x - txt->width + 1) * 4] + fog_percentage * (FOG >> 24 \
		& 255)) << 24;
	color |= (int)((1 - fog_percentage) * txt->pixels[txt->width * \
		ray.tex_y * 4 + ft_abs(ray.tex_x - txt->width + 1) * 4 + 1] + \
		fog_percentage * (FOG >> 16 & 255)) << 16;
	color |= (int)((1 - fog_percentage) * txt->pixels[txt->width * ray.tex_y * \
		4 + ft_abs(ray.tex_x - txt->width + 1) * 4 + 2] + fog_percentage * \
		(FOG >> 8 & 255)) << 8;
	color |= txt->pixels[txt->width * ray.tex_y * 4 + ft_abs(ray.tex_x - \
		txt->width + 1) * 4 + 3];
	return (color);
}

static void	entities_raycaster_set_var(t_player pl, \
	t_raycaster_entity *ray)
{
	ray->sprite_x = ray->entity.pos.x - pl.pos.x;
	ray->sprite_y = ray->entity.pos.y - pl.pos.y;
	ray->inv_det = 1.0 / (pl.plane.x * pl.facing.y - \
		pl.facing.x * pl.plane.y);
	ray->transform_x = ray->inv_det * (pl.facing.y * ray->sprite_x - \
		pl.facing.x * ray->sprite_y);
	ray->transform_y = ray->inv_det * (-pl.plane.y * ray->sprite_x + pl.plane.x \
		* ray->sprite_y);
	ray->sprite_screen_x = (int)((WIDTH / 2) * (1 + ray->transform_x / \
		ray->transform_y));
	ray->sprite_height = ft_abs((int)(HEIGHT / (ray->transform_y)));
	ray->draw_start_y = -ray->sprite_height / 2 + HEIGHT / 2;
	ray->draw_end_y = ray->sprite_height / 2 + HEIGHT / 2;
	ray->sprite_width = ft_abs((int)(HEIGHT / (ray->transform_y)));
	ray->draw_start_x = -ray->sprite_width / 2 + ray->sprite_screen_x;
	if (ray->draw_start_x < 0)
		ray->draw_start_x = 0;
	ray->draw_end_x = ray->sprite_width / 2 + ray->sprite_screen_x;
	if (ray->draw_end_x >= WIDTH)
		ray->draw_end_x = WIDTH - 1;
	ray->stripe = ray->draw_start_x;
}

static void	draw_stripe(t_cub *cb, t_raycaster_entity *ray)
{
	uint32_t	color;
	int			d;

	ray->tex_x = (int)(256 * (ray->stripe - (-ray->sprite_width / 2 + \
		ray->sprite_screen_x)) * ray->entity.texture->width / \
		ray->sprite_width) / 256;
	if (ray->transform_y > 0 && ray->stripe > 0 && ray->stripe < WIDTH && \
		ray->transform_y < cb->z_buffer[ray->stripe])
	{
		ray->y = ray->draw_start_y;
		while (ray->y < ray->draw_end_y)
		{
			d = (ray->y) * 256 - HEIGHT * 128 + ray->sprite_height * 128;
			ray->tex_y = ((d * ray->entity.texture->height) / \
				ray->sprite_height) / 256;
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
		while (ray.stripe < ray.draw_end_x)
		{
			draw_stripe(cb, &ray);
			ray.stripe++;
		}
	}
}
