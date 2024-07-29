/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:33:26 by bvasseur          #+#    #+#             */
/*   Updated: 2024/07/17 14:26:32 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	free(array);
}

int	find_max_len(char **file, int start, int height)
{
	int	len;
	int	i;
	int	j;

	i = 0;
	len = 0;
	while (i < height)
	{
		j = 0;
		while (file[start][j])
			j++;
		if (file[start][j - 1] == '\n')
			j--;
		if (j > len)
			len = j;
		start++;
		i++;
	}
	return (len);
}

int	is_in_bounds(int x, int y, int width, int height)
{
	return (x >= 0 && x < width && y >= 0 && y < height);
}
