/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons_interaction_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:11:05 by amolbert          #+#    #+#             */
/*   Updated: 2024/07/04 14:15:46 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

static void	change_first_to_second(t_cub *cb)
{
	if ((cb->weapon.flag % 100) / 10 == 1)
	{
		cb->weapon.first_weapon[0]->enabled = 0;
		cb->weapon.second_weapon[0]->enabled = 1;
		cb->weapon.flag = 211;
	}
	else if ((cb->weapon.flag % 100) / 10 == 2)
	{
		cb->weapon.first_weapon[1]->enabled = 0;
		cb->weapon.second_weapon[1]->enabled = 1;
		if ((cb->weapon.flag % 100) % 10 == 1)
			cb->weapon.flag = 221;
		else if ((cb->weapon.flag % 100) % 10 == 3)
			cb->weapon.flag = 223;
	}
	else if ((cb->weapon.flag % 100) / 10 == 3)
	{
		cb->weapon.first_weapon[2]->enabled = 0;
		cb->weapon.second_weapon[2]->enabled = 1;
		cb->weapon.flag = 232;
	}
}

static void	change_second_to_first(t_cub *cb)
{
	if ((cb->weapon.flag % 100) / 10 == 1)
	{
		cb->weapon.second_weapon[0]->enabled = 0;
		cb->weapon.first_weapon[0]->enabled = 1;
		cb->weapon.flag = 111;
	}
	else if ((cb->weapon.flag % 100) / 10 == 2)
	{
		cb->weapon.second_weapon[1]->enabled = 0;
		cb->weapon.first_weapon[1]->enabled = 1;
		if ((cb->weapon.flag % 100) % 10 == 1)
			cb->weapon.flag = 121;
		else if ((cb->weapon.flag % 100) % 10 == 3)
			cb->weapon.flag = 123;
	}
	else if ((cb->weapon.flag % 100) / 10 == 3)
	{
		cb->weapon.second_weapon[2]->enabled = 0;
		cb->weapon.first_weapon[2]->enabled = 1;
		cb->weapon.flag = 132;
	}
}

void	change_weapon(t_cub *cb)
{
	if (cb->weapon.flag / 100 == 1 && !cb->pause.image->enabled)
		change_first_to_second(cb);
	else if (cb->weapon.flag / 100 == 2 && !cb->pause.image->enabled)
		change_second_to_first(cb);
}
