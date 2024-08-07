/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:32:54 by bvasseur          #+#    #+#             */
/*   Updated: 2024/07/15 14:03:20 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	launch_mlx(t_cub *cb)
{
	cb->player.fov = 66;
	cb->player.length_plane = tan(cb->player.fov / 2 * (M_PI / 180));
	cb->player.plane = set_vector(cb->player.length_plane * \
			-cb->player.facing.y, cb->player.length_plane
			* cb->player.facing.x);
	cb->map.bozo_texture = mlx_load_png("textures/bozo.png");
	if (!cb->map.bozo_texture)
		error(cb, MISSING_ESSENTIAL_TEXTURE_ERROR);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	cb->mlx = mlx_init(WIDTH, HEIGHT, "3dcub", true);
	cb->image = mlx_new_image(cb->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(cb->mlx, cb->image, 0, 0);
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
	cb.map.height = ft_maplen(cb.map.map);
	launch_mlx(&cb);
	unleak(&cb);
	return (0);
}
