/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unleak_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:23:45 by bvasseur          #+#    #+#             */
/*   Updated: 2024/07/29 13:43:31 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

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

void	ft_delete_weapons(t_cub *cb)
{
	ft_delete_textures(2, cb->weapon.first_texture, \
	cb->weapon.second_texture);
	if (cb->weapon.first_weapon)
	{
		ft_delete_images(cb, 3, cb->weapon.first_weapon[0], \
		cb->weapon.first_weapon[1], cb->weapon.first_weapon[2]);
		free(cb->weapon.first_weapon);
	}
	if (cb->weapon.second_weapon)
	{
		ft_delete_images(cb, 3, cb->weapon.second_weapon[0], \
		cb->weapon.second_weapon[1], cb->weapon.second_weapon[2]);
		free(cb->weapon.second_weapon);
	}
}

void	unleak(t_cub *cb)
{
	int	i;

	if (!cb)
		return ;
	kill_sounds();
	ft_free_map(cb->map.file, ft_maplen(cb->map.file));
	ft_free_map(cb->map.map, ft_maplen(cb->map.map));
	ft_free_map(cb->map.param, 7);
	ft_free_ptr(2, cb->map.par, cb->doors);
	delete_img_text(cb);
	i = -1;
	while (++i < cb->pause.buttons_count)
		free_button(cb, cb->pause.buttons[i]);
	i = -1;
	while (++i < cb->pause.sliders_count)
		free_slider(cb, cb->pause.sliders[i]);
	ft_free_ptr(5, cb->pause.buttons, cb->pause.sliders, cb->entities, \
	cb->weapon.first_weapon, cb->weapon.second_weapon);
	if (cb->mlx)
		mlx_terminate(cb->mlx);
}
