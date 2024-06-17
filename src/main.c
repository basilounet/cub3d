/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:32:54 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/14 11:09:17 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	launch_mlx(t_cub *cb)
{
	cb->player.pos = set_vector(15, 10);
	cb->player.fov = 66;
	cb->player.facing = set_vector(0, -1);
	cb->player.length_plane = tan(cb->player.fov / 2 * (M_PI / 180));
	cb->player.plane = set_vector(cb->player.length_plane * -cb->player.facing.y,
		cb->player.length_plane * cb->player.plane.x);
	printf("facing : [%f, %f], plane : [%f, %f]\n", cb->player.facing.x, cb->player.facing.y, cb->player.plane.x, cb->player.plane.y);
	cb->map.floor_color = 0xAFF09AFF;
	cb->map.ceiling_color = 0x00AFFFFF;

	// mlx_set_setting(MLX_MAXIMIZED, true);
	// mlx_set_setting(MLX_STRETCH_IMAGE, true);
	cb->mlx = mlx_init(WIDTH, HEIGHT, "3dcub", false);
	cb->image = mlx_new_image(cb->mlx, WIDTH, HEIGHT);
	cb->minimap = mlx_new_image(cb->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	mlx_image_to_window(cb->mlx, cb->image, 0, 0);
	mlx_image_to_window(cb->mlx, cb->minimap, 10, 10);
	mlx_set_mouse_pos(cb->mlx, WIDTH / 2, HEIGHT / 2);
	mlx_key_hook(cb->mlx, ft_key_hook, cb);
	mlx_loop_hook(cb->mlx, ft_loop_hook, cb);
	mlx_loop(cb->mlx);
	mlx_delete_image(cb->mlx, cb->image);
	mlx_terminate(cb->mlx);
}

int32_t	main(int argc, char **argv)
{
	t_cub	cb;

	if (argc != 2)
		error(NULL, ARG_ERROR);
	parse(&cb, argv[1]);
	launch_mlx(&cb);
	unleak(&cb);
	return (0);
}
