/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:33:53 by bvasseur          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/06/13 13:30:47 by bvasseur         ###   ########.fr       */
=======
/*   Updated: 2024/06/12 11:44:40 by amolbert         ###   ########.fr       */
>>>>>>> f0ab2366798c9c3fb12bbea86c12d97f522c8df3
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
# define MINIMAP_WIDTH 150
# define MINIMAP_HEIGHT 150
# define MINIMAP_SQUARE_SIZE 15
# define ROTATION_SPEED 0.04
# define MOUSE_ROTATION_SPEED 0.0005
# define MOVE_SPEED 0.07

# ifndef DEBUG
#  define DEBUG 0
# endif

# ifndef BONUS
#  define BONUS 1
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

typedef struct s_raycaster
{
	int				step_x;
	int				step_y;
	int				map_x;
	int				map_y;
	t_vector		camera;
	t_vector		raydir;
	t_vector		side_dist;
	t_vector		delta_dist;
	double			perpWallDist;
	int				hit;
	int				side;
	int				lineHeight;
	int				drawStart;
	int				drawEnd;
}					t_raycaster;

typedef struct s_player
{
	t_vector		pos;
	t_vector		facing;
	t_vector		plane;
	double			length_plane;
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

typedef struct s_bresenham
{
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				err;
	int				e2;
}					t_bresenham;

/*=============== PARSER ===============*/

void				parse(t_cub *cb, char *arg);

/*=============== RAYTRACER ===============*/

void				raycaster(t_cub *cb);

/*=============== MOVMENT ===============*/

void				update_player_facing(t_cub *cb);
void				change_pos(t_cub *cb);

/*=============== MLX ===============*/

void				ft_loop_hook(void *param);
void				ft_key_hook(mlx_key_data_t keydata, void *param);

/*=============== DRAW ===============*/

void				try_put_pixel(mlx_image_t *img, uint32_t x, uint32_t y,
						int color);
void				draw_map(t_cub *cb);
void				draw_rectangle(mlx_image_t *img, t_vector pos,
						t_vector size, int color);
void				draw_empty_rectangle(mlx_image_t *img, t_vector pos,
						t_vector size, int color);
void				draw_triangle(mlx_image_t *img, t_vector pos,
						t_vector facing, int color);
void				draw_line(mlx_image_t *img, t_vector p0, t_vector p1,
						int color);
void				draw_map(t_cub *cb);

/*=============== UTILS ===============*/

t_vector			set_vector(double x, double y);
t_vector			add_vector(t_vector vec1, t_vector vec2);
t_vector			substract_vector(t_vector vec1, t_vector vec2);
t_vector			multiply_vector(t_vector vec1, t_vector vec2);
double				vector_length(t_vector vec);

/*=============== UNLEAK ===============*/

void				unleak(t_cub *cb);

/*=============== ERROR ===============*/

void				error(t_cub *cb, int error_num);

#endif