/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:03:38 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/06 15:12:01 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_vector    set_vector(double x, double y)
{
    t_vector    result_vector;

    result_vector.x = x;
    result_vector.y = y;
    return (result_vector);
}

t_vector    add_vector(t_vector vec1, t_vector vec2)
{
    t_vector    result_vector;

    result_vector.x = vec1.x + vec2.x;
    result_vector.y = vec1.y + vec2.y;
    return (result_vector);
}

t_vector    substract_vector(t_vector vec1, t_vector vec2)
{
    t_vector    result_vector;

    result_vector.x = vec1.x - vec2.x;
    result_vector.y = vec1.y - vec2.y;
    return (result_vector);
}

t_vector    multiply_vector(t_vector vec1, t_vector vec2)
{
    t_vector    result_vector;

    result_vector.x = vec1.x * vec2.x;
    result_vector.y = vec1.y * vec2.y;
    return (result_vector);
}
