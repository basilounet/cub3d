/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:59:12 by amolbert          #+#    #+#             */
/*   Updated: 2024/06/25 14:21:07 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	color_floor(t_cub *cb, int tmp, int count)
{
	if (count == 1)
	{
		cb->map.floor_color = tmp;
	}
	else if (count == 2)
	{
		cb->map.floor_color = (cb->map.floor_color << 8) + tmp;
	}
	else
	{
		cb->map.floor_color = (cb->map.floor_color << 8) + tmp;
		cb->map.floor_color = (cb->map.floor_color << 8) + 255;
	}
}

static void	color_ceiling(t_cub *cb, int tmp, int count)
{
	if (count == 1)
		cb->map.ceiling_color = tmp;
	else if (count == 2)
		cb->map.ceiling_color = (cb->map.ceiling_color << 8) + tmp;
	else
	{
		cb->map.ceiling_color = (cb->map.ceiling_color << 8) + tmp;
		cb->map.ceiling_color = (cb->map.ceiling_color << 8) + 255;
	}
}

void	save_color(t_cub *cb, char *color, int count, char *id)
{
	int	tmp;

	tmp = ft_atoi(color);
	if (!ft_strncmp(id, "F", 2))
		color_floor(cb, tmp, count);
	else
		color_ceiling(cb, tmp, count);
}
