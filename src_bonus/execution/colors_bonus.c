/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:33:04 by bvasseur          #+#    #+#             */
/*   Updated: 2024/07/30 16:15:35 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

static int	is_in_light(int x, int y)
{
	return (ft_abs(x - WIDTH / 2) <= HEIGHT * LIGHT_SIZE && \
		ft_abs(y - HEIGHT / 2) <= HEIGHT * LIGHT_SIZE);
}

double	get_light_percentage(int x, int y)
{
	double	dx;
	double	dy;
	double	percentage;

	dx = x - WIDTH / 2;
	dy = y - HEIGHT / 2;
	percentage = 1.0 - (sqrt(dx * dx + dy * dy) / (LIGHT_SIZE * HEIGHT));
	return (ft_fclamp(percentage, 0.0, 1.0));
}

int	get_color(t_cub *cb, t_raycaster *ray, mlx_texture_t *txt)
{
	double	fog_percentage;
	double	light_percentage;
	int		color;

	light_percentage = 0;
	if (cb->flags & LIGHT_ON && is_in_light(ray->x, ray->y))
		light_percentage = get_light_percentage(ray->x, ray->y);
	fog_percentage = ft_fclamp(ray->perp_wall_dist / (FOG_DISTANCE + \
		light_percentage * LIGHT_DISTANCE_MULTIPLIER * FOG_DISTANCE), 0, 1);
	color = (int)((1 - fog_percentage) * txt->pixels[txt->width * ray->tex_y \
		* 4 + ft_abs(ray->tex_x - txt->width + 1) * 4] + fog_percentage * \
		(FOG >> 24 & 255)) << 24;
	color |= (int)((1 - fog_percentage) * txt->pixels[txt->width * ray->tex_y \
		* 4 + ft_abs(ray->tex_x - txt->width + 1) * 4 + 1] + fog_percentage * \
		(FOG >> 16 & 255)) << 16;
	color |= (int)((1 - fog_percentage) * txt->pixels[txt->width * ray->tex_y \
		* 4 + ft_abs(ray->tex_x - txt->width + 1) * 4 + 2] + fog_percentage * \
		(FOG >> 8 & 255)) << 8;
	color |= txt->pixels[txt->width * ray->tex_y * 4 + ft_abs(ray->tex_x - \
		txt->width + 1) * 4 + 3];
	return (color);
}

static void	draw_screen_set_vars(t_cub *cb, t_raycaster *ray)
{
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2 + cb->player.pitch + \
		(ft_fclamp(cos(cb->player.jiggle), -.7, .7) * JIGGLE_FORCE / \
		ray->perp_wall_dist);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2 + cb->player.pitch + \
		(ft_fclamp(cos(cb->player.jiggle), -.7, .7) * JIGGLE_FORCE / \
		ray->perp_wall_dist);
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
	if (ray->side == 0)
		ray->wall_x = cb->player.pos.y + ray->perp_wall_dist * ray->raydir.y;
	else
		ray->wall_x = cb->player.pos.x + ray->perp_wall_dist * ray->raydir.x;
	ray->wall_x -= floor(ray->wall_x);
}

void	draw_screen(t_cub *cb, t_raycaster *ray)
{
	mlx_texture_t	*txt;

	draw_screen_set_vars(cb, ray);
	txt = get_wall_texture(cb, ray);
	ray->tex_x = (int)ft_fclamp((ray->wall_x * (double)(txt->width - 1)) + \
		(ray->is_door * (1 - ray->hit_door.timer) * (double)(txt->width - \
		1)), 0, txt->width - 1);
	if (!ray->is_door && ((ray->side == 0 && ray->raydir.x > 0) || (ray->side \
		== 1 && ray->raydir.y < 0)))
		ray->tex_x = txt->width - ray->tex_x - 1;
	ray->step = 1.0 * txt->height / ray->line_height;
	ray->tex_pos = (ray->draw_start - HEIGHT / 2 - cb->player.pitch - \
		(ft_fclamp(cos(cb->player.jiggle), -.7, .7) * JIGGLE_FORCE / \
		ray->perp_wall_dist) + ray->line_height / 2) * ray->step;
	ray->y = ray->draw_start;
	while (ray->y < ray->draw_end)
	{
		ray->tex_y = (int)ray->tex_pos & (txt->height - 1);
		ray->tex_pos += ray->step;
		try_put_pixel(cb->image, ray->x, ray->y + 1, get_color(cb, ray, txt));
		ray->y++;
	}
}
