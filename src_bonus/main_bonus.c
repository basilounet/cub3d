/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 12:34:05 by bvasseur          #+#    #+#             */
/*   Updated: 2024/07/29 21:21:27 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>
#include <time.h>

void	set_cb_values(t_cub *cb)
{
	srand(time(NULL));
	cb->player.key_rotation_speed = ROTATION_SPEED;
	cb->player.mouse_rotation_speed = MOUSE_ROTATION_SPEED;
	cb->player.fov = 66;
	cb->player.length_plane = tan(cb->player.fov / 2 * (M_PI / 180));
	cb->player.plane = set_vector(cb->player.length_plane * \
		-cb->player.facing.y, cb->player.length_plane * cb->player.facing.x);
	cb->player.last_step_sound = 0;
	cb->minimap.height = MINIMAP_HEIGHT;
	cb->minimap.width = MINIMAP_WIDTH;
	cb->minimap.square_size = MINIMAP_SQUARE_SIZE;
	cb->flags = FIRST_PLAY | PAUSE | LIGHT_ON;
}

void	launch_mlx(t_cub *cb)
{
	set_cb_values(cb);
	cb->mlx = mlx_init(WIDTH, HEIGHT, "3dcub", true);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_set_window_pos(cb->mlx, 0, 0);
	cb->image = mlx_new_image(cb->mlx, WIDTH, HEIGHT);
	cb->minimap.image = mlx_new_image(cb->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	cb->map.death_image = mlx_texture_to_image(cb->mlx, \
		cb->map.you_died_texture);
	cb->map.win_image = mlx_texture_to_image(cb->mlx, cb->map.you_win_texture);
	if (!cb->image || !cb->minimap.image || !cb->map.death_image || \
	!cb->map.win_image)
		error(cb, MLX_ERROR);
	mlx_image_to_window(cb->mlx, cb->image, 0, 0);
	mlx_image_to_window(cb->mlx, cb->minimap.image, 10, 10);
	display_weapon(cb);
	create_pause_screen(cb);
	scale_2_3(cb);
	mlx_key_hook(cb->mlx, ft_key_hook, cb);
	mlx_mouse_hook(cb->mlx, ft_mouse_hook, cb);
	mlx_loop_hook(cb->mlx, ft_loop_hook, cb);
	raycaster(cb);
	change_weapon(cb);
	mlx_loop(cb->mlx);
}

int	main(int argc, char **argv)
{
	t_cub	cb;

	if (argc != 2)
		error(NULL, ARG_ERROR);
	parse(&cb, argv[1]);
	launch_mlx(&cb);
	unleak(&cb);
	return (0);
}
