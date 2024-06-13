/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:33:53 by bvasseur          #+#    #+#             */
/*   Updated: 2024/06/12 11:44:40 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <MLX42/MLX42.h>
# include <libft.h>
# include <math.h>
# include <stdio.h>
# define WIDTH 612
# define HEIGHT 612
# define MINIMAP_WIDTH 600
# define MINIMAP_HEIGHT 300
# define MINIMAP_SQUARE_SIZE 30
# define ROTATION_SPEED 0.08
# define MOUSE_ROTATION_SPEED 0.001
# define MOVE_SPEED 0.11

# ifndef DEBUG
#  define DEBUG 0
# endif

enum				e_errors
{
	MALLOC_ERROR = 1,
	PATH_ERROR = 2,
	NAME_ERROR = 3,
	COLOR_ERROR = 4,
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
	char			**file;
	char			**map;
	int				width;
	int				height;
	int				floor_color;
	int				ceiling_color;
	mlx_texture_t	*north_texture;
	mlx_texture_t	*west_texture;
	mlx_texture_t	*south_texture;
	mlx_texture_t	*east_texture;
}					t_map;

typedef struct s_cub
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	mlx_image_t		*minimap;
	t_map			map;
	t_player		player;
}					t_cub;

typedef struct s_rectangle
{
	t_vector		pos;
	t_vector		size;
}					t_rectangle;

/*=============== PARSER ===============*/

void				parse(t_cub *cb, char *arg);

/*=============== RAYTRACER ===============*/

void				raycaster(t_cub *cb);

/*=============== MOVMENT ===============*/

void				change_pos(t_cub *cb);

/*=============== MLX ===============*/

void				ft_loop_hook(void *param);
void				ft_key_hook(mlx_key_data_t keydata, void *param);

/*=============== DRAW ===============*/

void	draw_map(t_cub *cb);
void				draw_rectangle(mlx_image_t *img, t_vector pos,
						t_vector size, int color);
void				draw_empty_rectangle(mlx_image_t *img, t_vector pos,
						t_vector size, int color);
void				draw_triangle(mlx_image_t *img, t_vector pos,
						t_vector facing, int color);

/*=============== UTILS ===============*/

t_vector			set_vector(double x, double y);
t_vector			add_vector(t_vector vec1, t_vector vec2);
t_vector			substract_vector(t_vector vec1, t_vector vec2);
t_vector			multiply_vector(t_vector vec1, t_vector vec2);
t_vector			normalize_vector(t_vector v);
void free_array(char **array);

/*=============== UNLEAK ===============*/

void				unleak(t_cub *cb);

/*=============== ERROR ===============*/

void				error(t_cub *cb, int error_num);

#endif