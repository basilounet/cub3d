/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:27:04 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/17 16:21:10 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	error(t_cub *cb, int error_num)
{
	char	*error_msg[] = {"A malloc error occured", "Wrong path's format", "Wrong name extension", "Wrong color's format", "Wrong numbers of arguments", "Wrong size map", "Map's parameters missing", "Wrong parameter's format", NULL};

	ft_putstr_fd("Error\n /!\\ ERROR /!\\ : ", 2);
	if (error_num > 0 && error_num < FINAL)
		ft_putendl_fd(error_msg[error_num - 1], 2);
    else
		ft_putendl_fd("Unknown error", 2);
    unleak(cb);
	exit(error_num);
}
