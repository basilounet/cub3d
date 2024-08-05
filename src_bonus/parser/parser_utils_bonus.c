/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:49:57 by amolbert          #+#    #+#             */
/*   Updated: 2024/07/31 17:01:22 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	save_entities(t_cub *cb, int i, int	*k)
{
	int	j;

	j = -1;
	while (cb->map.map[i][++j])
	{
		if (cb->map.map[i][j] == 'I')
		{
			cb->entities[*k].pos = set_vector(j + .5, i + .5);
			cb->entities[*k].texture = cb->map.item_texture;
			cb->entities[*k].type = ITEM;
			cb->nb_of_items++;
			(*k)++;
		}
		else if (cb->map.map[i][j] == 'M')
		{
			cb->entities[*k].pos = set_vector(j + .5, i + .5);
			cb->entities[*k].facing = set_vector(1, 0);
			cb->entities[*k].fov = 90;
			cb->entities[*k].speed = ENEMY_SPEED;
			cb->entities[*k].player_dist = 0;
			cb->entities[*k].texture = cb->map.enemy_texture;
			cb->entities[*k].type = ENEMY;
			(*k)++;
		}
	}
}

void	load_png(t_cub *cb)
{
	cb->map.enemy_texture = mlx_load_png("textures/enemy.png");
	cb->map.enemy_back_texture = mlx_load_png("textures/enemy_back.png");
	cb->map.item_texture = mlx_load_png("textures/banana.png");
	cb->map.you_win_texture = mlx_load_png("textures/You_win.png");
	cb->map.you_died_texture = mlx_load_png("textures/You_died.png");
	cb->map.bozo_texture = mlx_load_png("textures/bozo.png");
	cb->map.door_texture = mlx_load_png("textures/door.png");
	if (!cb->map.item_texture || !cb->map.enemy_texture || \
		!cb->map.enemy_back_texture || !cb->map.you_win_texture || \
		!cb->map.you_died_texture || !cb->map.bozo_texture || \
		!cb->map.door_texture)
		error(cb, MISSING_ESSENTIAL_TEXTURE_ERROR);
}

void	fill_map(t_cub *cb, int i, int j, int len)
{
	while (j < len)
	{
		cb->map.map[i][j] = '\0';
		j++;
	}
}

int	is_impediment(char c)
{
	return (c == '1' || c == ' ' || c == '\n' || c == '\0');
}
