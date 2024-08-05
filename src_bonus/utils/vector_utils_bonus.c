/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:03:38 by bvasseur          #+#    #+#             */
/*   Updated: 2024/07/31 13:21:42 by amolbert         ###   ########.fr       */
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

double	vector_length(t_vector vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y));
}

t_vector	normalize_vector(t_vector v)
{
	double	length;

	length = sqrt(v.x * v.x + v.y * v.y);
	return ((t_vector){v.x / length, v.y / length});
}

double	dot_product(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}
