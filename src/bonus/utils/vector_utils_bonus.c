/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:03:38 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/27 18:47:38 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

t_vector	set_vector(double x, double y)
{
	t_vector	result_vector;

	result_vector.x = x;
	result_vector.y = y;
	return (result_vector);
}

t_vector	multiply_vector(t_vector vector, double multiplier)
{
	t_vector	result_vector;

	result_vector.x = vector.x * multiplier;
	result_vector.y = vector.y * multiplier;
	return (result_vector);
}


double	vector_length(t_vector vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y));
}
