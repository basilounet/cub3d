/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:46:25 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/11 16:24:01 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	get_minimap_symbol_color(t_map map, int x, int y)
{
	if (y < 0 || y > map.height - 1 || x < 0 || x > (int)ft_strlen(map.map[y]))
		return (0x0000FFFF);
	if (map.map[y][x] == '0')
		return (0x00FF00FF);
	if (map.map[y][x] == '1')
		return (0x000000FF);
	return (0x0000FFFF);
}

void	draw_map(t_cub *cb)
{
	int	x;
	int	y;
	
	ft_memset(cb->minimap->pixels, 0xFFFFFFFF, cb->minimap->height
		* cb->minimap->width * 4);	
	y = cb->player.pos.y - MINIMAP_HEIGHT / MINIMAP_SQUARE_SIZE / 2 - 1;
	while (y < cb->player.pos.y + MINIMAP_HEIGHT / MINIMAP_SQUARE_SIZE / 2 + 2)
	{
		x = cb->player.pos.x - MINIMAP_WIDTH / MINIMAP_SQUARE_SIZE / 2 - 1;
		while (x < cb->player.pos.x + MINIMAP_WIDTH / MINIMAP_SQUARE_SIZE / 2
			+ 2)
		{
			// printf("num case : x : %d, y : %d, color %X\n", x, y, get_minimap_symbol_color(cb->map, x, y));
			draw_rectangle(cb->minimap, set_vector(ft_clamp((x
							- cb->player.pos.x + MINIMAP_WIDTH
							/ MINIMAP_SQUARE_SIZE / 2) * MINIMAP_SQUARE_SIZE, 0,
						MINIMAP_WIDTH), ft_clamp((y - cb->player.pos.y
							+ MINIMAP_HEIGHT / MINIMAP_SQUARE_SIZE / 2)
						* MINIMAP_SQUARE_SIZE, 0, MINIMAP_HEIGHT)),
				set_vector(MINIMAP_SQUARE_SIZE, MINIMAP_SQUARE_SIZE),
				get_minimap_symbol_color(cb->map, x, y));
			x++;
		}
		y++;
	}
	draw_empty_rectangle(cb->minimap, set_vector(0, 0),
		set_vector(MINIMAP_WIDTH, MINIMAP_HEIGHT), 0x0000FFFF);
	draw_triangle(cb->minimap, set_vector(MINIMAP_WIDTH / 2 , MINIMAP_HEIGHT / 2), cb->player.facing, 0xFF0000FF);
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
	// printf("player pos : [%f, %f]\n", cb->player.pos.x, cb->player.pos.y);
	new_x = cb->player.pos.x + offset.x;
	new_y = cb->player.pos.y + offset.y;
	// printf("new pos : [%f, %f]\n\n", new_x, new_y);
	if (new_x >= 0 && new_x < cb->map.width && new_y >= 0
		&& new_y < cb->map.height
		&& cb->map.map[(int)floor(new_y)][(int)floor(new_x)] != '1')
		cb->player.pos = set_vector(new_x, new_y);
}
