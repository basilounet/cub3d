/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:14:02 by amolbert          #+#    #+#             */
/*   Updated: 2024/07/04 09:47:01 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

long long	timediff(t_cub *cb)
{
	long long	diff;

	diff = timestamp() - cb->weapon.time;
	return (diff);
}

long long	timestamp(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		write(2, "gettimeofday() error\n", 22);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
