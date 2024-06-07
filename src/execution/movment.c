/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:46:25 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/07 20:39:33 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	get_minimap_symbol_color(t_map map, int x, int y)
{
	if (x < 0 || x > map.widht || y < 0 || y > map.height - 1)
		return (0x00000000);
	if (map.map[y][x] == '0')
		return (0x00FF00FF);
	if (map.map[y][x] == '1')
		return (0x000000FF);
	return (0x00000000);
}

void	draw_map(t_cub *cb)
{
	int	x;
	int	y;

	ft_memset(cb->minimap->pixels, 0xFFFFFFFF, cb->minimap->height
		* cb->minimap->width * 4);
	y = cb->player.pos.y - MINIMAP_HEIGHT / MINIMAP_SQUARE_SIZE / 2;
	while (y < cb->player.pos.y + MINIMAP_HEIGHT / MINIMAP_SQUARE_SIZE / 2)
	{
		x = cb->player.pos.x - MINIMAP_WIDTH / MINIMAP_SQUARE_SIZE / 2;
		while (x < cb->player.pos.x + MINIMAP_WIDTH / MINIMAP_SQUARE_SIZE / 2)
		{
			draw_rectangle(cb->minimap, set_vector((x - cb->player.pos.x
						+ MINIMAP_WIDTH / MINIMAP_SQUARE_SIZE / 2)
					* MINIMAP_SQUARE_SIZE, (y - cb->player.pos.y
						+ MINIMAP_HEIGHT / MINIMAP_SQUARE_SIZE / 2)
					* MINIMAP_SQUARE_SIZE), set_vector(MINIMAP_SQUARE_SIZE,
					MINIMAP_SQUARE_SIZE), get_minimap_symbol_color(cb->map, x,
					y));
			x++;
		}
		y++;
	}
	draw_empty_rectangle(cb->minimap, set_vector(0, 0),
		set_vector(MINIMAP_WIDTH, MINIMAP_HEIGHT), 0x0000FFFF);
	draw_rectangle(cb->minimap, set_vector(MINIMAP_WIDTH / 2
			- MINIMAP_SQUARE_SIZE / 2, MINIMAP_HEIGHT / 2 - MINIMAP_SQUARE_SIZE
			/ 2), set_vector(MINIMAP_SQUARE_SIZE, MINIMAP_SQUARE_SIZE),
		0xFF0000FF);
}

void	change_pos(t_cub *cb, double x_offset, double y_offset)
{
	double	new_x;
	double	new_y;

	new_x = cb->player.pos.x + x_offset;
	new_y = cb->player.pos.y + y_offset;
	if (new_x >= 0 && new_x < cb->map.widht && new_y >= 0
		&& new_y < cb->map.height
		&& cb->map.map[(int)round(new_y)][(int)round(new_x)] != '1')
		cb->player.pos = set_vector(new_x, new_y);
	draw_map(cb);
	// printf("new_x : %f, new_y : %f, symbol : %c\n", new_x, new_y,
	// cb->map.map[(int)new_y][(int)(new_y)]);
	// printf("x : %f, y : %f\n", cb->player.pos.x, cb->player.pos.y);
}
