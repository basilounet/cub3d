/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:46:25 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/13 13:07:06 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	update_player_facing(t_cub *cb)
{
	double	angle;
	int32_t	x;
	int32_t	y;

	angle = 0;
	mlx_get_mouse_pos(cb->mlx, &x, &y);
	if (BONUS)
		angle += (x - WIDTH / 2) * MOUSE_ROTATION_SPEED;
	if (mlx_is_key_down(cb->mlx, MLX_KEY_LEFT))
		angle -= ROTATION_SPEED;
	if (mlx_is_key_down(cb->mlx, MLX_KEY_RIGHT))
		angle += ROTATION_SPEED;
	if (angle != 0)
	{
		cb->player.facing = set_vector(cb->player.facing.x * cos(angle)
				- cb->player.facing.y * sin(angle), cb->player.facing.x
				* sin(angle) + cb->player.facing.y * cos(angle));
		cb->player.plane = set_vector(cb->player.plane.x * cos(angle)
				- cb->player.plane.y * sin(angle), cb->player.plane.x
				* sin(angle) + cb->player.plane.y * cos(angle));
	}
	if (BONUS)
		mlx_set_mouse_pos(cb->mlx, WIDTH / 2, HEIGHT / 2);
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
	if (new_y >= 0 && new_y < cb->map.height && new_x >= 0
		&& new_x < ft_strlen(cb->map.map[(int)new_y])
		&& cb->map.map[(int)floor(new_y)][(int)floor(new_x)] != '1')
		cb->player.pos = set_vector(new_x, new_y);
}
