/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:46:25 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/09 16:39:53 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	get_minimap_symbol_color(t_map map, int x, int y)
{
	if (x < 0 || x > map.width || y < 0 || y > map.height - 1)
		return (0x00000000);
	if (map.map[y][x] == '0')
		return (0x00FF00FF);
	if (x == 11 && y == 12)
		return (0xFF0000FF);
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
	draw_triangle(cb->minimap, set_vector(MINIMAP_WIDTH / 2, MINIMAP_HEIGHT
			/ 2 + MINIMAP_SQUARE_SIZE), cb->player.facing, 0xFF0000FF);
}

void	change_pos(t_cub *cb)
{
	t_vector	lateral;
	t_vector	offset;
	double		new_x;
	double		new_y;

	offset = set_vector(0, 0);
	lateral = set_vector(cb->player.facing.y, -cb->player.facing.x);
	if (mlx_is_key_down(cb->mlx, MLX_KEY_W))
		offset = set_vector(offset.x + cb->player.facing.x * MOVE_SPEED,
				offset.y + cb->player.facing.y * MOVE_SPEED);
	if (mlx_is_key_down(cb->mlx, MLX_KEY_S))
		offset = set_vector(offset.x - cb->player.facing.x * MOVE_SPEED,
				offset.y - cb->player.facing.y * MOVE_SPEED);
	if (mlx_is_key_down(cb->mlx, MLX_KEY_D))
		offset = set_vector(offset.x - lateral.x * MOVE_SPEED, offset.y
				- lateral.y * MOVE_SPEED);
	if (mlx_is_key_down(cb->mlx, MLX_KEY_A))
		offset = set_vector(offset.x + lateral.x * MOVE_SPEED, offset.y
				+ lateral.y * MOVE_SPEED);
	new_x = cb->player.pos.x + offset.x;
	new_y = cb->player.pos.y + offset.y;
	if (new_x >= 0 && new_x < cb->map.width && new_y >= 0
		&& new_y < cb->map.height
		&& cb->map.map[(int)round(new_y)][(int)round(new_x)] != '1')
		cb->player.pos = set_vector(new_x, new_y);
}
