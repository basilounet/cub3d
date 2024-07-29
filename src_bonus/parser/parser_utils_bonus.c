/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:49:57 by amolbert          #+#    #+#             */
/*   Updated: 2024/07/29 13:24:09 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	load_png(t_cub *cb)
{
	cb->map.enemy_texture = mlx_load_png("textures/enemy.png");
	cb->map.enemy_back_texture = mlx_load_png("textures/enemy_back.png");
	cb->map.item_texture = mlx_load_png("textures/banana.png");
	cb->map.you_win_texture = mlx_load_png("textures/You_win.png");
	cb->map.you_died_texture = mlx_load_png("textures/You_died.png");
	cb->map.bozo_texture = mlx_load_png("textures/bozo.png");
	cb->map.door_texture = mlx_load_png("textures/door.png");
	if (!cb->map.item_texture || !cb->map.enemy_texture || !cb->map.enemy_back_texture || 
		!cb->map.you_win_texture || !cb->map.you_died_texture || !cb->map.bozo_texture ||
		!cb->map.door_texture)
		error(cb, MISSING_ESSENTIAL_TEXTURE_ERROR);
}

void	fill_map(char **map, int i, int j, int len)
{
	while (j < len)
	{
		map[i][j] = '\0';
		j++;
	}
}
