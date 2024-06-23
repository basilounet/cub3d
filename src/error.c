/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:27:04 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/22 17:15:44 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	error(t_cub *cb, int error_num)
{
	char	*error_msg[] = {"A malloc error occured", "Wrong path's format",
			"Wrong name extension", "Wrong color's format",
			"Wrong numbers of arguments", "Wrong size map",
			"Map's parameters missing", "Wrong parameter's format",
			"Empty line in the map", "Wrong character in the map",
			"One player is necessary", "Map must be closed",
			"Too many arguments on line", "The file does not exists", NULL};

	ft_putstr_fd("Error\n /!\\ ERROR /!\\ : ", 2);
	if (error_num > 0 && error_num < FINAL)
		ft_putendl_fd(error_msg[error_num - 1], 2);
	else
		ft_putendl_fd("Unknown error", 2);
	unleak(cb);
	exit(error_num);
}
