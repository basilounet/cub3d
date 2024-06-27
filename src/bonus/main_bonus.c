/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:32:54 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/27 11:31:54 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	create_pause_screen(t_cub *cb, int action)
{
	int	i;

	if (action == 0)
		cb->pause.image = mlx_new_image(cb->mlx, cb->width, cb->height);
	else
		mlx_resize_image(cb->pause.image ,cb->width, cb->height);
	i = 0;
	while (i < cb->width * cb->height * 4)
	{
		cb->pause.image->pixels[i] = (PAUSE_MENU_COLOR >> 24) & 255;
		cb->pause.image->pixels[i + 1] = (PAUSE_MENU_COLOR >> 16) & 255;
		cb->pause.image->pixels[i + 2] = (PAUSE_MENU_COLOR >> 8) & 255;
		cb->pause.image->pixels[i + 3] = (PAUSE_MENU_COLOR) & 255;
		i += 4;
	}
	if (action == 1)
		return ;
	cb->pause.image->enabled = 0;
	cb->pause.buttons_count = 1;
	cb->pause.buttons = ft_calloc(sizeof(t_button), cb->pause.buttons_count + 1);
	if (!cb->pause.buttons)
		error(cb, MALLOC_ERROR);
	mlx_image_to_window(cb->mlx, cb->pause.image, 0, 0);
}

void	launch_mlx(t_cub *cb)
{
	cb->player.pos = set_vector(5, 5);
	cb->player.facing = set_vector(0, -1);
	cb->width = WIDTH;
	cb->height = HEIGHT;
	cb->player.fov = 66;
	cb->player.length_plane = tan(cb->player.fov / 2 * (M_PI / 180));
	cb->player.plane = set_vector(cb->player.length_plane * \
			-cb->player.facing.y, cb->player.length_plane * cb->player.plane.x);
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
	mlx_set_mouse_pos(cb->mlx, cb->width / 2, cb->height / 2);
	mlx_key_hook(cb->mlx, ft_key_hook, cb);
	mlx_loop_hook(cb->mlx, ft_loop_hook, cb);
	mlx_resize_hook(cb->mlx, ft_resize_hook, cb);
	mlx_loop(cb->mlx);
	mlx_delete_image(cb->mlx, cb->image);
	mlx_delete_image(cb->mlx, cb->minimap.image);
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
