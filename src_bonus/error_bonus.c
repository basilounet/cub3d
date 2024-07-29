/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:27:04 by bvasseur          #+#    #+#             */
/*   Updated: 2024/07/17 09:41:47 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	error(t_cub *cb, int error_num)
{
	static char	*error_msg[] = {"A malloc error occured", "Wrong path format",
		"Wrong name extension", "Wrong color format",
		"Wrong numbers of arguments", "Wrong size map",
		"Map parameters missing", "Wrong parameter format",
		"Empty line in the map", "Wrong character in the map",
		"One player is necessary", "Map must be closed",
		"Too many arguments on line", "The file does not exists",
		"One of the essential textures is missing \
		(enemy, enemy_back, bozo, door)", "An MLX error occured",
		"Doors must be placed between the walls", NULL};

	ft_putstr_fd("Error\n /!\\ ERROR /!\\ : ", 2);
	if (error_num > 0 && error_num < MAX_ERROR)
		ft_putendl_fd(error_msg[error_num - 1], 2);
	else
		ft_putendl_fd("Unknown error", 2);
	unleak(cb);
	exit(error_num);
}
