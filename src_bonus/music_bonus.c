/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 09:39:19 by amolbert          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/07/30 11:33:27 by bvasseur         ###   ########.fr       */
=======
/*   Updated: 2024/07/31 08:52:20 by amolbert         ###   ########.fr       */
>>>>>>> 74fd9b119d0e5b28523db29d9e062ab58f7cad87
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	player_step_sound(t_cub *cb)
{
	int	random;

<<<<<<< HEAD
	if ((int)cb->player.jiggle % 6 == 0 && \
		cb->player.last_step_sound != (int)cb->player.jiggle)
=======
	if ((int)cb->player.jiggle % 6 == 0 && cb->player.last_step_sound != \
	(int)cb->player.jiggle)
>>>>>>> 74fd9b119d0e5b28523db29d9e062ab58f7cad87
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
