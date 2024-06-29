/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unleak_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:23:45 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/27 17:56:49 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	*ft_delete_textures(int nb, ...)
{
	va_list	list;
	void	*ptr;

	va_start(list, nb);
	while (nb > 0)
	{
		ptr = va_arg(list, void *);
		if (ptr)
		{
			mlx_delete_texture(ptr);
			ptr = NULL;
		}
		nb--;
	}
	va_end(list);
	return (NULL);
}

void	*ft_delete_images(t_cub *cb, int nb, ...)
{
	va_list	list;
	void	*ptr;

	va_start(list, nb);
	while (nb > 0)
	{
		ptr = va_arg(list, void *);
		if (ptr)
		{
			mlx_delete_image(cb->mlx, ptr);
			ptr = NULL;
		}
		nb--;
	}
	va_end(list);
	return (NULL);
}

void	free_bonuses(t_cub *cb)
{
	int	i;

	i = -1;
	while (++i < cb->pause.buttons_count)
	{
		ft_free_ptr(3, cb->pause.buttons[i].name, cb->pause.buttons[i].text,
			cb->pause.buttons[i].txt_name);
		ft_delete_images(cb, 2, cb->pause.buttons[i].bg,
			cb->pause.buttons[i].text_img);
		ft_delete_textures(1, cb->pause.buttons[i].txt);
	}
	if (cb->pause.buttons)
		free(cb->pause.buttons);
}

void	unleak(t_cub *cb)
{
	if (!cb)
		return ;
	if (cb->map.file)
		ft_free_map(cb->map.file, ft_maplen(cb->map.file));
	if (cb->map.map)
		ft_free_map(cb->map.map, ft_maplen(cb->map.map));
	if (cb->map.param)
		ft_free_map(cb->map.param, 7);
	if (cb->map.par)
		free(cb->map.par);
	ft_delete_textures(5, cb->map.north_texture, cb->map.west_texture,
		cb->map.south_texture, cb->map.east_texture, cb->map.bozo_texture);
	free_bonuses(cb);
}
