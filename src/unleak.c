/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unleak.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:23:45 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/06 14:45:34 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void    unleak(t_cub *cb)
{
    if (cb->map.map)
        ft_free_map(cb->map.map, cb->map.height);
}