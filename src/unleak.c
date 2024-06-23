/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unleak.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:23:45 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/22 17:19:56 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	unleak(t_cub *cb)
{
	if (!cb)
		return ;
	if (cb->map.file)
		ft_free_map(cb->map.file, ft_maplen(cb->map.file));
	if (cb->map.map)
		ft_free_map(cb->map.map, ft_maplen(cb->map.map));
	if (cb->map.param)
		ft_free_map(cb->map.param, 7);
	if (cb->map.par)
		free(cb->map.par);
	if (cb->map.north_texture)
		mlx_delete_texture(cb->map.north_texture);
	if (cb->map.west_texture)
		mlx_delete_texture(cb->map.west_texture);
	if (cb->map.south_texture)
		mlx_delete_texture(cb->map.south_texture);
	if (cb->map.east_texture)
		mlx_delete_texture(cb->map.east_texture);
}
