/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fmax.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:56:20 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/30 16:57:49 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

double	ft_fmax(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

double	ft_fmin(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

double	ft_fclamp(double value, double min, double max)
{
	return (ft_fmax(min, ft_fmin(max, value)));
}
