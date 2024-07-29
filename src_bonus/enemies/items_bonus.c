/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:32:14 by bvasseur          #+#    #+#             */
/*   Updated: 2024/07/19 15:37:41 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

static void	check_win(t_cub *cb)
{
	static int	count = 0;

	if (cb->count_items == cb->nb_of_items)
	{
		kill_sounds();
		cb->flags |= DEAD;
		if (count == 0)
			cb->flags ^= PAUSE;
		mlx_image_to_window(cb->mlx, cb->map.win_image, 0, 0);
		count++;
		usleep(40000);
		if (count >= 150)
			mlx_close_window(cb->mlx);
	}
}

void	check_collect_items(t_cub *cb, t_player pl, t_entity *entities, int *nb)
{
	t_entity	item;
	int			i;
	int			j;

	i = -1;
	while (++i < *nb)
	{
		if (entities[i].type == ITEM)
		{
			item = entities[i];
			if (pl.pos.x > item.pos.x - .5 && pl.pos.x < item.pos.x + .5 && \
				pl.pos.y > item.pos.y - .5 && pl.pos.y < item.pos.y + .5)
			{
				j = i;
				while (j < *nb)
				{
					entities[i] = entities[i + 1];
					cb->count_items++;
					j++;
				}
				(*nb)--;
			}
		}
	}
	check_win(cb);
}
