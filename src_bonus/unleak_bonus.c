/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unleak_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:23:45 by bvasseur          #+#    #+#             */
/*   Updated: 2024/07/01 16:09:56 by bvasseur         ###   ########.fr       */
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

void	free_button(t_cub *cb, t_button button)
{
	ft_free_ptr(2, button.text, button.txt_name);
	ft_delete_images(cb, 2, button.bg, button.text_img);
	ft_delete_textures(1, button.txt);
}

void	free_slider(t_cub *cb, t_slider slider)
{
	free_button(cb, slider.slider);
	free_button(cb, slider.button);
}

void	unleak(t_cub *cb)
{
	int	i;

	if (!cb)
		return ;
	ft_free_map(cb->map.file, ft_maplen(cb->map.file));
	ft_free_map(cb->map.map, ft_maplen(cb->map.map));
	ft_free_map(cb->map.param, 7);
	ft_free_ptr(1, cb->map.par);
	ft_delete_textures(5, cb->map.north_texture, cb->map.west_texture,
		cb->map.south_texture, cb->map.east_texture, cb->map.bozo_texture);
	ft_delete_images(cb, 3, cb->image, cb->minimap.image, cb->pause.image);
	i = -1;
	while (++i < cb->pause.buttons_count)
		free_button(cb, cb->pause.buttons[i]);
	i = -1;
	while (++i < cb->pause.sliders_count)
		free_slider(cb, cb->pause.sliders[i]);
	ft_free_ptr(2, cb->pause.buttons, cb->pause.sliders);
	if (cb->mlx)
		mlx_terminate(cb->mlx);
}
