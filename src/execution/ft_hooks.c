/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:47:10 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/10 13:41:38 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

typedef void (*mlx_cursorfunc)(double xpos, double ypos, void* param);


void	update_player_facing(t_cub *cb)
{
	double	angle;
	double	current_angle;
	int32_t	x;
	int32_t	y;

	angle = 0;
	mlx_get_mouse_pos(cb->mlx, &x, &y);
	angle += (x - WIDTH / 2) * MOUSE_ROTATION_SPEED;
	if (mlx_is_key_down(cb->mlx, MLX_KEY_LEFT))
		angle -= ROTATION_SPEED;
	if (mlx_is_key_down(cb->mlx, MLX_KEY_RIGHT))
		angle += ROTATION_SPEED;
	if (angle != 0)
	{
		current_angle = atan2(cb->player.facing.y, cb->player.facing.x);
		current_angle += angle;
		cb->player.facing.x = cos(current_angle);
		cb->player.facing.y = sin(current_angle);
	}
	mlx_set_mouse_pos(cb->mlx, WIDTH / 2, HEIGHT / 2);
}

void	ft_loop_hook(void *param)
{
	t_cub	*cb;

	cb = (t_cub *)param;
	update_player_facing(cb);
	change_pos(cb);
	// printf("facing x : %f, y : %f\n", cb->player.facing.x, cb->player.facing.y);
	draw_map(cb);
	draw_rectangle(cb->minimap, set_vector(MINIMAP_WIDTH / 2 - 3, MINIMAP_HEIGHT / 2 - 3), set_vector(6, 6), 0xFFFFFFFF);
}

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_cub	*cb;

	cb = (t_cub *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(cb->mlx);
}
