/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:22:44 by amolbert          #+#    #+#             */
/*   Updated: 2024/07/15 15:54:48 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

static void	display_first_weapon(t_cub *cb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!i)
			cb->weapon.first_weapon[i]->enabled = 1;
		else
			cb->weapon.first_weapon[i]->enabled = 0;
		mlx_image_to_window(cb->mlx, cb->weapon.first_weapon[i], \
		HEIGHT, 200 - (i * 10));
		i++;
	}
}

static void	save_first_weapon(t_cub *cb)
{
	int			i;

	i = 0;
	cb->weapon.first_texture = mlx_load_png("textures/babanana.png");
	if (!cb->weapon.first_texture)
		error(cb, MISSING_ESSENTIAL_TEXTURE_ERROR);
	cb->weapon.first_weapon = ft_calloc(sizeof(mlx_image_t), 3);
	if (!cb->weapon.first_weapon)
		error(cb, MALLOC_ERROR);
	while (i < 3)
	{
		cb->weapon.first_weapon[i] = \
		mlx_texture_to_image(cb->mlx, cb->weapon.first_texture);
		if (!cb->weapon.first_weapon[i])
			error(cb, MISSING_ESSENTIAL_TEXTURE_ERROR);
		i++;
	}
	cb->weapon.time = timestamp();
	cb->weapon.flag = 110;
	display_first_weapon(cb);
}

static void	save_second_weapon(t_cub *cb)
{
	int	i;

	i = 0;
	cb->weapon.second_texture = mlx_load_png("textures/babananaked.png");
	if (!cb->weapon.second_texture)
		error(cb, MISSING_ESSENTIAL_TEXTURE_ERROR);
	cb->weapon.second_weapon = ft_calloc(sizeof(mlx_image_t), 3);
	if (!cb->weapon.second_weapon)
		error(cb, MALLOC_ERROR);
	while (i < 3)
	{
		cb->weapon.second_weapon[i] = \
		mlx_texture_to_image(cb->mlx, cb->weapon.second_texture);
		if (!cb->weapon.second_weapon[i])
			error(cb, MISSING_ESSENTIAL_TEXTURE_ERROR);
		cb->weapon.second_weapon[i]->enabled = 0;
		mlx_image_to_window(cb->mlx, cb->weapon.second_weapon[i], \
		HEIGHT, 200 - (i * 10));
		i++;
	}
}

void	display_weapon(t_cub *cb)
{
	save_first_weapon(cb);
	save_second_weapon(cb);
}
