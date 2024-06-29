/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:27:04 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/27 17:58:40 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	error(t_cub *cb, int error_num)
{
	static char	*error_msg[] = {"A malloc error occured", "Wrong path's format",
			"Wrong name extension", "Wrong color's format",
			"Wrong numbers of arguments", "Wrong size map",
			"Map's parameters missing", "Wrong parameter's format",
			"Empty line in the map", "Wrong character in the map",
			"One player is necessary", "Map must be closed",
			"Too many arguments on line", "The file does not exists",
			"The bozo png is missing",
			"An Error occured with one of the mlx functions", NULL};

	ft_putstr_fd("Error\n /!\\ ERROR /!\\ : ", 2);
	if (error_num > 0 && error_num < MAX_ERROR)
		ft_putendl_fd(error_msg[error_num - 1], 2);
	else
		ft_putendl_fd("Unknown error", 2);
	unleak(cb);
	exit(error_num);
}
