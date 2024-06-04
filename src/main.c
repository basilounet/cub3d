/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:32:54 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/04 16:39:06 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int32_t main(void)
{
	mlx_t* mlx;

	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);
    mlx_new_image(mlx, 128, 128);
	
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
