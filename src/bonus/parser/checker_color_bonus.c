/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_color_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:18:54 by amolbert          #+#    #+#             */
/*   Updated: 2024/06/27 13:10:27 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

static int	check_size_arg(char *arg)
{
	int	i;
	int	s;

	i = 0;
	s = 0;
	while (arg[i])
	{
		if (s * 10 + (arg[i] - '0') > 255)
			return (1);
		s = s * 10 + (arg[i] - '0');
		i++;
	}
	return (0);
}

static int	check_color3(char **color, int j)
{
	int	k;

	k = 0;
	while (color[j][k])
	{
		if (color[j][k] == '\n')
			color[j][k] = '\0';
		k++;
	}
	k = 0;
	if (color[j] == NULL || color[j][k] == '\0')
		return (1);
	while (ft_isdigit(color[j][k]))
		k++;
	if (color[j][k])
		return (1);
	return (0);
}

static int	check_color2(t_cub *cb, char **color, int *count, char *id)
{
	int	j;

	j = 0;
	while (color[j])
	{
		if (color[j][0] == '\n')
			break ;
		if (check_color3(color, j))
			return (1);
		if (check_size_arg(color[j]))
			return (1);
		(*count)++;
		save_color(cb, color[j], *count, id);
		j++;
	}
	return (0);
}

int	check_color(t_cub *cb, char **line, char *id)
{
	int		i;
	int		count;
	char	**color;

	i = 1;
	count = 0;
	while (line[i])
	{
		color = ft_split(line[i], ',');
		if (!color)
			return (2);
		if (check_color2(cb, color, &count, id))
		{
			free_array(color);
			return (1);
		}
		free_array(color);
		i++;
	}
	if (count != 3)
		return (1);
	return (0);
}
