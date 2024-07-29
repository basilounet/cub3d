/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_weapons_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:09:44 by amolbert          #+#    #+#             */
/*   Updated: 2024/07/04 14:12:31 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

static void	animate_first_weapon(t_cub *cb, int i, int j, int flag)
{
	cb->weapon.first_weapon[i]->enabled = 0;
	cb->weapon.first_weapon[j]->enabled = 1;
	cb->weapon.flag = flag;
	cb->weapon.time = timestamp();
}

static void	animate_second_weapon(t_cub *cb, int i, int j, int flag)
{
	cb->weapon.second_weapon[i]->enabled = 0;
	cb->weapon.second_weapon[j]->enabled = 1;
	cb->weapon.flag = flag;
	cb->weapon.time = timestamp();
}

static void	animation_first_weapon(t_cub *cb)
{
	if ((cb->weapon.flag % 100) / 10 == 1)
	{
		if (timediff(cb) > 500)
			animate_first_weapon(cb, 0, 1, 121);
	}
	else if ((cb->weapon.flag % 100) / 10 == 2)
	{
		if ((cb->weapon.flag % 100) % 10 == 1)
			if (timediff(cb) > 500)
				animate_first_weapon(cb, 1, 2, 132);
		if ((cb->weapon.flag % 100) % 10 == 3)
			if (timediff(cb) > 500)
				animate_first_weapon(cb, 1, 0, 112);
	}
	else if ((cb->weapon.flag % 100) / 10 == 3)
	{
		if (timestamp () - cb->weapon.time > 500)
			animate_first_weapon(cb, 2, 1, 123);
	}
}

static void	animation_second_weapon(t_cub *cb)
{
	if ((cb->weapon.flag % 100) / 10 == 1)
	{
		if (timediff(cb) > 500)
			animate_second_weapon(cb, 0, 1, 221);
	}
	else if ((cb->weapon.flag % 100) / 10 == 2)
	{
		if ((cb->weapon.flag % 100) % 10 == 1)
			if (timediff(cb) > 500)
				animate_second_weapon(cb, 1, 2, 232);
		if ((cb->weapon.flag % 100) % 10 == 3)
			if (timediff(cb) > 500)
				animate_second_weapon(cb, 1, 0, 212);
	}
	else if ((cb->weapon.flag % 100) / 10 == 3)
	{
		if (timestamp () - cb->weapon.time > 500)
			animate_second_weapon(cb, 2, 1, 223);
	}
}

void	animate_weapon(t_cub *cb)
{
	if (cb->weapon.flag / 100 == 1)
		animation_first_weapon(cb);
	else
		animation_second_weapon(cb);
}
