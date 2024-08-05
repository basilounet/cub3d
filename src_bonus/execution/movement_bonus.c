/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:09:26 by amolbert          #+#    #+#             */
/*   Updated: 2024/07/31 16:09:28 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

static void	update_vertical_player_facing(t_cub *cb, int y)
{
	if (mlx_is_key_down(cb->mlx, MLX_KEY_UP))
		y -= cb->player.key_rotation_speed * 1000;
	if (mlx_is_key_down(cb->mlx, MLX_KEY_DOWN))
		y += cb->player.key_rotation_speed * 1000;
	cb->player.pitch = ft_clamp(cb->player.pitch - ((y - cb->mlx->height / 2) \
		* (cb->player.mouse_rotation_speed * 1000)), -HEIGHT / 2, HEIGHT / 2);
}

void	update_player_facing(t_cub *cb)
{
	double	angle;
	int32_t	x;
	int32_t	y;

	angle = 0;
	mlx_get_mouse_pos(cb->mlx, &x, &y);
	angle += (x - cb->mlx->width / 2) * cb->player.mouse_rotation_speed;
	if (mlx_is_key_down(cb->mlx, MLX_KEY_LEFT))
		angle -= cb->player.key_rotation_speed;
	if (mlx_is_key_down(cb->mlx, MLX_KEY_RIGHT))
		angle += cb->player.key_rotation_speed;
	if (angle != 0)
	{
		cb->player.facing = set_vector(cb->player.facing.x * cos(angle)
				- cb->player.facing.y * sin(angle), cb->player.facing.x
				* sin(angle) + cb->player.facing.y * cos(angle));
		cb->player.plane = set_vector(cb->player.plane.x * cos(angle)
				- cb->player.plane.y * sin(angle), cb->player.plane.x
				* sin(angle) + cb->player.plane.y * cos(angle));
	}
	update_vertical_player_facing(cb, y);
	mlx_set_mouse_pos(cb->mlx, cb->mlx->width / 2, cb->mlx->height / 2);
}

t_vector	clip_to_wall(t_cub *cb, t_vector old_pos, t_vector pos)
{
	t_vector	new_pos;

	new_pos = pos;
	if (pos.y - .1 < 0 || pos.y + .1 >= cb->map.height || pos.x - .1 < 0 || \
		pos.x + .1 >= ft_strlen(cb->map.map[(int)pos.y]))
		return (old_pos);
	if (cb->flags & GOD)
		return (new_pos);
	if (cb->map.map[(int)(pos.y + .1)][(int)pos.x] == '1')
		new_pos.y = ceil(pos.y) - .1;
	if (cb->map.map[(int)(pos.y - .1)][(int)pos.x] == '1')
		new_pos.y = floor(pos.y) + .1;
	if (cb->map.map[(int)pos.y][(int)(pos.x + .1)] == '1')
		new_pos.x = ceil(pos.x) - .1;
	if (cb->map.map[(int)pos.y][(int)(pos.x - .1)] == '1')
		new_pos.x = floor(pos.x) + .1;
	if (cb->map.map[(int)new_pos.y][(int)new_pos.x] == '1')
		new_pos = old_pos;
	return (new_pos);
}

void	change_pos(t_cub *cb)
{
	t_vector	lateral;
	t_vector	offset;
	t_vector	new_pos;

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
	new_pos = set_vector(cb->player.pos.x + offset.x, cb->player.pos.y + \
		offset.y);
	if (new_pos.y >= 0 && new_pos.y < cb->map.height && \
		new_pos.x >= 0 && new_pos.x < ft_strlen(cb->map.map[(int)new_pos.y]))
		cb->player.pos = clip_to_wall(cb, cb->player.pos, new_pos);
	if (offset.x != 0 || offset.y != 0)
		cb->player.jiggle += JIGGLE_SPEED;
}
