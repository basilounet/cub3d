/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_ai_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:32:14 by bvasseur          #+#    #+#             */
/*   Updated: 2024/07/30 12:58:35 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	is_player_in_vision(t_player player, t_entity enemy, int fov)
{
	double		half_fov_radians;
	double		cos_half_fov;
	t_vector	to_player;
	double		dot;

	to_player = normalize_vector(set_vector(player.pos.x - enemy.pos.x, \
	player.pos.y - enemy.pos.y));
	dot = dot_product(enemy.facing, to_player);
	half_fov_radians = (fov / 2.0) * (M_PI / 180.0);
	cos_half_fov = cos(half_fov_radians);
	return (dot >= cos_half_fov);
}

t_vector	clip_to_wall_enemy(t_cub *cb, t_vector old_pos, t_vector pos, \
int enemy_nb)
{
	int			i;
	t_vector	new_pos;

	new_pos = pos;
	if (pos.y - .2 < 0 || pos.y + .2 >= cb->map.height || pos.x - .2 < 0 || \
		pos.x + .2 >= ft_strlen(cb->map.map[(int)pos.y]))
		return (old_pos);
	update_pos(cb, &new_pos, pos, old_pos);
	i = -1;
	while (++i < cb->nb_of_entities)
		if (cb->entities[i].type == ENEMY)
			if (i != enemy_nb && new_pos.x > cb->entities[i].pos.x - .1 && \
			new_pos.x < cb->entities[i].pos.x + .1 && new_pos.y > \
			cb->entities[i].pos.y - .1 && new_pos.y < cb->entities[i].pos.y \
			+ .1)
				return (old_pos);
	return (new_pos);
}

void	check_player_collision(t_cub *cb, t_player pl, t_entity *entities, \
	int nb)
{
	static int	count = 0;
	t_entity	enemy;
	int			i;

	i = -1;
	while (++i < nb && (cb->flags & GOD) == 0)
	{
		if (entities[i].type == ENEMY)
		{
			enemy = entities[i];
			if (pl.pos.x > enemy.pos.x - .55 && pl.pos.x < enemy.pos.x + .55 && \
				pl.pos.y > enemy.pos.y - .55 && pl.pos.y < enemy.pos.y + .55)
			{
				cb->flags |= DEAD;
				if (count == 0)
					cb->flags ^= PAUSE;
				mlx_image_to_window(cb->mlx, cb->map.death_image, 0, 0);
				count++;
				usleep(40000);
				if (count >= 150)
					mlx_close_window(cb->mlx);
				return ;
			}
		}
	}
}

static void	set_move(t_cub *cb, t_entity *enemy, int i)
{
	double		angle;

	if (is_player_in_vision(cb->player, *enemy, enemy->fov) && \
	vector_length(set_vector(cb->player.pos.x - enemy->pos.x, \
	cb->player.pos.y - enemy->pos.y)) < ENEMY_AGRO_RANGE)
	{
		enemy->facing = normalize_vector(set_vector(cb->player.pos.x - \
		enemy->pos.x, cb->player.pos.y - enemy->pos.y));
		enemy->pos = clip_to_wall_enemy(cb, enemy->pos, set_vector(enemy->pos.x \
		+ enemy->facing.x * enemy->speed, enemy->pos.y + enemy->facing.y * \
		enemy->speed), i);
	}
	else if (rand() % 50 == 42)
	{
		angle = (rand() % 3 - 1) / (rand() % 10 + .01);
		enemy->facing = set_vector(enemy->facing.x * cos(angle) \
		- enemy->facing.y * sin(angle), enemy->facing.x \
		* sin(angle) + enemy->facing.y * cos(angle));
		if (rand() % 3 == 0)
			enemy->pos = clip_to_wall_enemy(cb, enemy->pos, \
			set_vector(enemy->pos.x + enemy->facing.x * enemy->speed, \
			enemy->pos.y + enemy->facing.y * enemy->speed), i);
	}
}

void	move_enemy(t_cub *cb)
{
	t_entity	*enemy;
	int			i;

	i = -1;
	while (++i < cb->nb_of_entities)
	{
		if (cb->entities[i].type == ENEMY)
		{
			enemy = &cb->entities[i];
			set_move(cb, enemy, i);
		}
	}
}
