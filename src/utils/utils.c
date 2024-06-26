/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:33:26 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/25 14:41:45 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
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
