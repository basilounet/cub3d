/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:44:52 by amolbert          #+#    #+#             */
/*   Updated: 2024/06/25 14:46:03 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	param_full(t_cub *cb)
{
	if (!cb->map.floor_color)
		error(cb, MISSING_ERROR);
	if (!cb->map.ceiling_color)
		error(cb, MISSING_ERROR);
	if (!cb->map.north_texture)
		error(cb, MISSING_ERROR);
	if (!cb->map.west_texture)
		error(cb, MISSING_ERROR);
	if (!cb->map.south_texture)
		error(cb, MISSING_ERROR);
	if (!cb->map.east_texture)
		error(cb, MISSING_ERROR);
}

void	set_param(t_cub *cb)
{
	cb->map.param = ft_calloc(sizeof(char *), 7);
	cb->map.param[0] = ft_strdup("NO");
	cb->map.param[1] = ft_strdup("SO");
	cb->map.param[2] = ft_strdup("EA");
	cb->map.param[3] = ft_strdup("WE");
	cb->map.param[4] = ft_strdup("F");
	cb->map.param[5] = ft_strdup("C");
	if (!cb->map.param[0] || !cb->map.param[1] || !cb->map.param[2]
		|| !cb->map.param[3] || !cb->map.param[4] || !cb->map.param[5])
		error(cb, MALLOC_ERROR);
	cb->map.par = ft_calloc(sizeof(int), 7);
	if (!cb->map.par)
		error(cb, MALLOC_ERROR);
}
