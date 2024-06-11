/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:03:38 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/10 17:01:00 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_vector	set_vector(double x, double y)
{
	t_vector	result_vector;

	result_vector.x = x;
	result_vector.y = y;
	return (result_vector);
}

t_vector	add_vector(t_vector vec1, t_vector vec2)
{
	t_vector	result_vector;

	result_vector.x = vec1.x + vec2.x;
	result_vector.y = vec1.y + vec2.y;
	return (result_vector);
}

t_vector	substract_vector(t_vector vec1, t_vector vec2)
{
	t_vector	result_vector;

	result_vector.x = vec1.x - vec2.x;
	result_vector.y = vec1.y - vec2.y;
	return (result_vector);
}

t_vector	multiply_vector(t_vector vec1, t_vector vec2)
{
	t_vector	result_vector;

	result_vector.x = vec1.x * vec2.x;
	result_vector.y = vec1.y * vec2.y;
	return (result_vector);
}

t_vector	normalize_vector(t_vector vec)
{
	double	length;

	length = sqrt(vec.x * vec.x + vec.y * vec.y);
	if (length != 0)
	{
		vec.x /= length;
		vec.y /= length;
	}
    return (vec);
}

double	vector_length(t_vector vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y));
}
