/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:47:17 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/27 11:32:27 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

static int	get_minimap_symbol_color(t_cub *cb, t_map map, int x, int y)
{
	if (y < 0 || y > map.height - 1 || x < 0 || x > (int)ft_strlen(map.map[y]))
		return (0x0);
	if (map.map[y][x] == '1')
		return (switch_bit(cb->map.ceiling_color) | 0xFF);
	return (0x0);
}

void	draw_map(t_cub *cb, t_minimap mm)
{
	int	x;
	int	y;

	y = cb->player.pos.y - mm.height / mm.square_size / 2 - 1;
	while (y < cb->player.pos.y + mm.height / mm.square_size / 2 + 2)
	{
		x = cb->player.pos.x - mm.width / mm.square_size / 2 - 2;
		while (++x < cb->player.pos.x + mm.width / mm.square_size / 2 + 2)
			draw_rectangle(cb->minimap.image, set_vector(ft_clamp((x
							- cb->player.pos.x + mm.width / mm.square_size / 2)
						* mm.square_size, 0, mm.width), ft_clamp((y
							- cb->player.pos.y + mm.height / mm.square_size / 2)
						* mm.square_size, 0, mm.height)),
				set_vector(mm.square_size, mm.square_size),
				get_minimap_symbol_color(cb, cb->map, x, y));
		y++;
	}
	draw_empty_rectangle(cb->minimap.image, set_vector(0, 0),
		set_vector(mm.width, mm.height),
		switch_bit(cb->map.ceiling_color) | 0xFF);
	draw_triangle(cb->minimap.image, set_vector(mm.width / 2, mm.height / 2),
		cb->player.facing, switch_bit(cb->map.floor_color) | 0xFF);
}
