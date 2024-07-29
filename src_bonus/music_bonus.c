/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 09:39:19 by amolbert          #+#    #+#             */
/*   Updated: 2024/07/29 15:00:56 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	player_step_sound(t_cub *cb)
{
	int	random;
	
	if ((int)cb->player.jiggle % 6 == 0 && cb->player.last_step_sound != (int)cb->player.jiggle)
		cb->player.last_step_sound = (int)cb->player.jiggle;
	else 
		return ;
	random = rand() % 3;
	if (random == 0)
		play_sound("sounds/step_0.wav &");
	else if (random == 1)
		play_sound("sounds/step_1.wav &");
	else
		play_sound("sounds/step_2.wav &");
}

void	play_sound(char *path)
{
	char	*str;

	str = ft_strjoin("paplay ", path);
	if (!str)
		return ;
	system(str);
	free(str);
}

void	kill_sounds(void)
{
	system("pkill paplay &");
}
