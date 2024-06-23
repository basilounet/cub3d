/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:47:17 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/23 13:28:04 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	get_minimap_symbol_color(t_cub *cb, t_map map, int x, int y)
{
	if (y < 0 || y > map.height - 1 || x < 0 || x > (int)ft_strlen(map.map[y]))
		return (0x0);
	if (map.map[y][x] == '1')
		return (switch_bit(cb->map.ceiling_color) | 0xFF);
	return (0x0);
}

void	draw_map(t_cub *cb)
{
	int	x;
	int	y;

	y = cb->player.pos.y - MINIMAP_HEIGHT / MINIMAP_SQUARE_SIZE / 2 - 1;
	while (y < cb->player.pos.y + MINIMAP_HEIGHT / MINIMAP_SQUARE_SIZE / 2 + 2)
	{
		x = cb->player.pos.x - MINIMAP_WIDTH / MINIMAP_SQUARE_SIZE / 2 - 2;
		while (++x < cb->player.pos.x + MINIMAP_WIDTH / MINIMAP_SQUARE_SIZE / 2
			+ 2)
			draw_rectangle(cb->minimap, set_vector(ft_clamp((x
							- cb->player.pos.x + MINIMAP_WIDTH
							/ MINIMAP_SQUARE_SIZE / 2) * MINIMAP_SQUARE_SIZE, 0,
						MINIMAP_WIDTH), ft_clamp((y - cb->player.pos.y
							+ MINIMAP_HEIGHT / MINIMAP_SQUARE_SIZE / 2)
						* MINIMAP_SQUARE_SIZE, 0, MINIMAP_HEIGHT)),
				set_vector(MINIMAP_SQUARE_SIZE, MINIMAP_SQUARE_SIZE),
				get_minimap_symbol_color(cb, cb->map, x, y));
		y++;
	}
	draw_empty_rectangle(cb->minimap, set_vector(0, 0),
		set_vector(MINIMAP_WIDTH, MINIMAP_HEIGHT), switch_bit(cb->map.ceiling_color) | 0xFF);
	draw_triangle(cb->minimap, set_vector(MINIMAP_WIDTH / 2, MINIMAP_HEIGHT
			/ 2), cb->player.facing, switch_bit(cb->map.floor_color) | 0xFF);
}
