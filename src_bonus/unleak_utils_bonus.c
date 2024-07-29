/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unleak_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:23:45 by bvasseur          #+#    #+#             */
/*   Updated: 2024/07/17 14:23:41 by amolbert         ###   ########.fr       */
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

void	delete_img_text(t_cub *cb)
{
	ft_delete_textures(13, cb->map.north_texture, cb->map.west_texture,
		cb->map.south_texture, cb->map.east_texture, cb->map.bozo_texture,
		cb->map.enemy_texture, cb->map.enemy_back_texture, \
		cb->map.door_texture, cb->map.you_died_texture, \
		cb->map.item_texture, cb->map.you_win_texture, \
		cb->weapon.first_texture, cb->weapon.second_texture);
	ft_delete_images(cb, 10, cb->image, cb->minimap.image, \
	cb->pause.image, cb->map.death_image, cb->weapon.first_weapon[0], \
	cb->weapon.first_weapon[1], cb->weapon.first_weapon[2], \
	cb->weapon.second_weapon[0], cb->weapon.second_weapon[1], \
	cb->weapon.second_weapon[2]);
}
