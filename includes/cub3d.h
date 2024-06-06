/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:33:53 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/06 16:37:25 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <MLX42/MLX42.h>
# include <libft.h>
# include <math.h>
# include <stdio.h>
# define WIDTH 512
# define HEIGHT 512

# ifndef DEBUG
#  define DEBUG 0
# endif

enum				e_errors
{
	MALLOC_ERROR = 1,
	FINAL,
};

typedef struct s_vector
{
	double			x;
	double			y;
}					t_vector;

typedef struct s_player
{
	t_vector		pos;
	t_vector		facing;
	t_vector		plane;
	int				fov;
}					t_player;

typedef struct s_map
{
	char			**map;
	int				widht;
	int				height;
	int				floor_color;
	int				ceiling_color;
	mlx_texture_t	north_texture;
	mlx_texture_t	west_texture;
	mlx_texture_t	south_texture;
	mlx_texture_t	east_texture;
}					t_map;

typedef struct s_cub
{
	mlx_t			*mlx;
	t_map			map;
	t_player		player;
}					t_cub;

/*=============== PARSER ===============*/

void				parse(t_cub *cb);

/*=============== RAYTRACER ===============*/

void				raycaster(t_cub *cb);

/*=============== UTILS ===============*/

t_vector			set_vector(double x, double y);
t_vector			add_vector(t_vector vec1, t_vector vec2);
t_vector			substract_vector(t_vector vec1, t_vector vec2);
t_vector			multiply_vector(t_vector vec1, t_vector vec2);

/*=============== UNLEAK ===============*/

void				unleak(t_cub *cb);

/*=============== ERROR ===============*/

void				error(t_cub *cb, int error_num);

#endif