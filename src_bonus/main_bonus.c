/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:32:54 by bvasseur          #+#    #+#             */
/*   Updated: 2024/07/01 11:24:04 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	create_weapons_textures(t_cub *cb)
{
	(void)cb;
	//mlx_texture_t	*weapons_texture;
	//mlx_image_t		*weapons_image;
	
	//weapons_texture = mlx_load_png("textures/babanana.png");
	//if (!weapons_texture)
	//	error(cb, MISSING_BOZO_ERROR);
	//weapons_image = mlx_texture_to_image(cb->mlx, weapons_texture);
	//mlx_image_to_window(cb->mlx, weapons_image, 1000, 1000);
}

void	launch_mlx(t_cub *cb)
{
	cb->width = WIDTH;
	cb->height = HEIGHT;
	cb->player.fov = 66;
	cb->player.length_plane = tan(cb->player.fov / 2 * (M_PI / 180));
	cb->player.plane = set_vector(cb->player.length_plane *
			-cb->player.facing.y, cb->player.length_plane
			* cb->player.facing.x);
	cb->map.bozo_texture = mlx_load_png("textures/bozo.png");
	if (!cb->map.bozo_texture)
		error(cb, MISSING_BOZO_ERROR);
	cb->minimap.height = MINIMAP_HEIGHT;
	cb->minimap.width = MINIMAP_WIDTH;
	cb->minimap.square_size = MINIMAP_SQUARE_SIZE;
	// mlx_set_setting(MLX_MAXIMIZED, true);
	// mlx_set_setting(MLX_STRETCH_IMAGE, true);
	cb->mlx = mlx_init(cb->width, cb->height, "3dcub", true);
	cb->image = mlx_new_image(cb->mlx, cb->width, cb->height);
	cb->minimap.image = mlx_new_image(cb->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	mlx_image_to_window(cb->mlx, cb->image, 0, 0);
	mlx_image_to_window(cb->mlx, cb->minimap.image, 10, 10);
	create_pause_screen(cb, 0);
	create_weapons_textures(cb);
	mlx_set_mouse_pos(cb->mlx, cb->width / 2, cb->height / 2);
	mlx_key_hook(cb->mlx, ft_key_hook, cb);
	mlx_loop_hook(cb->mlx, ft_loop_hook, cb);
	mlx_resize_hook(cb->mlx, ft_resize_hook, cb);
	mlx_loop(cb->mlx);
	mlx_delete_image(cb->mlx, cb->image);
	mlx_delete_image(cb->mlx, cb->minimap.image);
	mlx_delete_image(cb->mlx, cb->pause.image);
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
