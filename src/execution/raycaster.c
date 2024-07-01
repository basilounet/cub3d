/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:59:53 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/27 13:22:22 by bvasseur         ###   ########.fr       */
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

mlx_texture_t	*get_wall_texture(t_cub *cb, t_raycaster *ray)
{
	if (cb->player.pos.y < 0 || cb->player.pos.y >= cb->map.height
		|| cb->player.pos.x < 0
		|| cb->player.pos.x >= ft_strlen(cb->map.map[(int)cb->player.pos.y])
		|| cb->map.map[(int)floor(cb->player.pos.y)][(int)floor(cb->player.pos.x)] != '0')
		return (cb->map.bozo_texture);
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

void	try_put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, int color)
{
	if (x < 0 || x > img->width || y < 0 || y > img->height)
		return ;
	mlx_put_pixel(img, x, y, color);
}

static void	draw_screen(t_cub *cb, t_raycaster *ray, int x)
{
	mlx_texture_t	*txt;
	int				texX;
	double			step;
	double			texPos;
	int				texY;
	int				color;

	double wallX; // where exactly the wall was hit
	ray->line_height = (int)(cb->height / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + cb->height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + cb->height / 2;
	if (ray->draw_end >= cb->height)
		ray->draw_end = cb->height - 1;
	if (ray->side == 0)
		wallX = cb->player.pos.y + ray->perp_wall_dist * ray->raydir.y;
	else
		wallX = cb->player.pos.x + ray->perp_wall_dist * ray->raydir.x;
	wallX -= floor(wallX);
	txt = get_wall_texture(cb, ray);
	texX = (int)(wallX * (double)txt->width);
	if ((ray->side == 0 && ray->raydir.x > 0) || (ray->side == 1
			&& ray->raydir.y < 0))
		texX = txt->width - texX - 1;
	step = 1.0 * txt->height / ray->line_height;
	texPos = (ray->draw_start - cb->height / 2 + ray->line_height / 2) * step;
	for (int y = ray->draw_start; y < ray->draw_end; y++)
	{
		texY = (int)texPos & (txt->height - 1);
		texPos += step;
		color = txt->pixels[txt->height * texY * 4 + ft_abs(texX - txt->width
				+ 1) * 4] << 24 | txt->pixels[txt->height * texY * 4
			+ ft_abs(texX - txt->width + 1) * 4
			+ 1] << 16 | txt->pixels[txt->height * texY * 4 + ft_abs(texX
				- txt->width + 1) * 4 + 2] << 8 | txt->pixels[txt->height * texY
			* 4 + ft_abs(texX - txt->width + 1) * 4 + 3];
		try_put_pixel(cb->image, x, y + 1, color);
	}
}

static void	raycaster_loop(t_cub *cb, t_player pl)
{
	t_raycaster	ray;
	int			x;

	x = 0;
	while (x < cb->width)
	{
		ray = (t_raycaster){0};
		ray.camera.x = 2 * x / (double)cb->width - 1;
		ray.raydir.x = pl.facing.x + pl.plane.x * ray.camera.x;
		ray.raydir.y = pl.facing.y + pl.plane.y * ray.camera.x;
		raycaster_set_var(cb->player, &ray);
		dda(cb, &ray);
		if (ray.side == 0)
			ray.perp_wall_dist = (ray.side_dist.x - ray.delta_dist.x);
		else
			ray.perp_wall_dist = (ray.side_dist.y - ray.delta_dist.y);
		if (ray.perp_wall_dist <= 0.1f)
			ray.perp_wall_dist = 1;
		draw_screen(cb, &ray, x);
		x++;
	}
}

void	raycaster(t_cub *cb)
{
	draw_rectangle(cb->image, set_vector(0, 0), set_vector(cb->width, cb->height / 2),
		cb->map.ceiling_color);
	draw_rectangle(cb->image, set_vector(0, cb->height / 2), set_vector(cb->width,
			cb->height / 2), cb->map.floor_color);
	raycaster_loop(cb, cb->player);
}
