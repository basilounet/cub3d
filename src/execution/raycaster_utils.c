/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:59:53 by bvasseur          #+#    #+#             */
/*   Updated: 2024/07/18 15:28:05 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

mlx_texture_t	*get_wall_texture(t_cub *cb, t_raycaster *ray)
{
	if (cb->player.pos.y < 0 || cb->player.pos.y >= cb->map.height || \
	cb->player.pos.x < 0 || cb->player.pos.x >= \
	ft_strlen(cb->map.map[(int)cb->player.pos.y]) || \
	cb->map.map[(int)floor(cb->player.pos.y)][(int)floor(cb->player.pos.x)] != \
	'0')
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

void	print_pixel(t_cub *cb, t_raycaster *ray, int x, mlx_texture_t *txt)
{
	int				y;

	y = ray->draw_start - 1;
	while (++y < ray->draw_end)
	{
		ray->tex_y = (int)ray->tex_pos & (txt->height - 1);
		ray->tex_pos += ray->step;
		ray->color = txt->pixels[txt->height * ray->tex_y * 4 + \
		ft_abs(ray->tex_x - txt->width + 1) * 4] << 24 | \
		txt->pixels[txt->height * ray->tex_y * 4 + ft_abs(ray->tex_x - \
		txt->width + 1) * 4 + 1] << 16 | txt->pixels[txt->height * ray->tex_y * \
		4 + ft_abs(ray->tex_x - txt->width + 1) * 4 + 2] << 8 | \
		txt->pixels[txt->height * ray->tex_y * 4 + ft_abs(ray->tex_x - \
		txt->width + 1) * 4 + 3];
		try_put_pixel(cb->image, x, y + 1, ray->color);
	}
}
