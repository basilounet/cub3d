/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:27:04 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/06 14:41:19 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	error(t_cub *cb, int error_num)
{
	char	*error_msg[] = {"A malloc error occured", NULL};

	ft_putstr_fd("Error\n /!\\ ERROR /!\\ : ", 2);
	if (error_num > 0 && error_num < FINAL - 1)
		ft_putendl_fd(error_msg[error_num], 2);
    else
		ft_putendl_fd("Unknown error", 2);
    unleak(cb);
	exit(error_num);
}
