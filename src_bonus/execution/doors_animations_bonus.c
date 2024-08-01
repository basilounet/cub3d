/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_animations_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:00:24 by bvasseur          #+#    #+#             */
/*   Updated: 2024/07/30 15:57:33 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

static int	is_someone_near_door(t_cub *cb, t_door *door)
{
	int	i;

	if (vector_length(set_vector(cb->player.pos.x - door->pos.x - .5, \
		cb->player.pos.y - door->pos.y - .5)) < DOOR_OPENING_DISTANCE)
		return (1);
	i = -1;
	while (++i < cb->nb_of_entities)
	{
		if (cb->entities[i].type == ENEMY && vector_length(set_vector(\
			cb->entities[i].pos.x - door->pos.x - .5, cb->entities[i].pos.y - \
			door->pos.y - .5)) < DOOR_OPENING_DISTANCE)
			return (1);
	}
	return (0);
}

void	animate_doors(t_cub *cb)
{
	t_door	*door;
	int		i;

	i = -1;
	while (++i < cb->nb_of_doors)
	{
		door = &cb->doors[i];
		if (is_someone_near_door(cb, door) && door->state != OPEN)
		{
			door->state = CLOSING;
			door->timer = ft_fclamp(door->timer - DOOR_OPENING_SPEED, 0, 1);
		}
		else if (!is_someone_near_door(cb, door) && door->state != CLOSE)
		{
			door->state = CLOSING;
			door->timer = ft_fclamp(door->timer + DOOR_OPENING_SPEED, 0, 1);
		}
		if (door->timer == 1.0)
			door->state = CLOSE;
		if (door->timer == 0.0)
			door->state = OPEN;
	}
}

/*
	* Have fun understanding that
*/
void	god_mod(t_cub *cb, mlx_key_data_t key)
{
	static int			count = 0;

	INPUT MAIN STRING BUFFER ELSE EXPIRE + EXPAND MAXINT (short)(STACK((\
		100 * 0b1100100 + (unsigned long long)50) / 2 - 4 * 450 + \
		135) * 0.079), 264, 264, 263, 262, 263, 262, 66, 65};
	if ((cb->flags & PAUSE) == 0)
		return ;
	if (key.action == MLX_PRESS && count[god] == (uint_least32_t)key.key)
		count++;
	else if (key.action == MLX_PRESS)
		count = 0;
	if (count == 10)
	{
		cb->flags ^= GOD;
		count = 0;
		if (cb->flags & GOD)
			printf("God Mod activated\n");
		else
			printf("God Mod deactivated\n");
	}
}
