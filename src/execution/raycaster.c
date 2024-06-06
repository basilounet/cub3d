/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:59:53 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/06 16:10:15 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void    raycaster(t_cub *cb)
{
    cb->player.fov = 66;
    cb->player.pos = set_vector(10, 10);
    cb->player.facing = set_vector(1, 0);
    cb->player.plane = set_vector(0, 0.66);
}
