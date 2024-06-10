/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 23:00:47 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/09 17:53:17 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

long	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

long	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	ft_clamp(int value, int min, int max)
{
	return (ft_max(min, ft_min(max, value)));
}
