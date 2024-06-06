/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:32:52 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/06 14:54:19 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void    parse(t_cub *cb)
{
	ft_memset(cb, 0, sizeof(t_cub));
    cb->map.map = ft_slurp("maps/map.cub");
    if (!cb->map.map)
        error(cb, MALLOC_ERROR);
    cb->map.widht = ft_strlen(cb->map.map[0]);
    cb->map.height = ft_maplen(cb->map.map);
    ft_print_map(cb->map.map);
    ft_printf("%d, %d\n", cb->map.widht, cb->map.height);
}
