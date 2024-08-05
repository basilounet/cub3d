/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:33:53 by bvasseur          #+#    #+#             */
/*   Updated: 2024/07/31 16:16:30 by amolbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <MLX42/MLX42.h>
# include <libft.h>
# include <math.h>
# include <stdio.h>
# define WIDTH 1000
# define HEIGHT 480
# define ROTATION_SPEED 0.04
# define MOVE_SPEED 0.05

# ifndef DEBUG
#  define DEBUG 0
# endif

enum				e_errors
{
	MALLOC_ERROR = 1,
	PATH_ERROR = 2,
	NAME_ERROR = 3,
	COLOR_ERROR = 4,
	ARG_ERROR = 5,
	HEIGHT_ERROR = 6,
	MISSING_ERROR = 7,
	PARAM_ERROR = 8,
	EMPTYLINE_ERROR = 9,
	BADCHAR_ERROR = 10,
	PLAYER_ERROR = 11,
	CLOSED_ERROR = 12,
	TOO_MANY_ARG_ON_LINE = 13,
	NO_FILE_ERROR = 14,
	MISSING_ESSENTIAL_TEXTURE_ERROR = 15,
	MAX_ERROR,
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
	double			perp_wall_dist;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				tex_x;
	double			step;
	double			tex_pos;
	int				tex_y;
	int				color;
	double			wall_x;
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
	char			**param;
	int				*par;
	int				width;
	int				height;
	int				height_file;
	int				floor_color;
	int				ceiling_color;
	mlx_texture_t	*north_texture;
	mlx_texture_t	*west_texture;
	mlx_texture_t	*south_texture;
	mlx_texture_t	*east_texture;
	mlx_texture_t	*bozo_texture;
}					t_map;

typedef struct s_cub
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_map			map;
	t_player		player;
}					t_cub;

/*=============== CHECKER PARAM ===============*/

int					check_param2(t_cub *cb, int i);

/*=============== CHECKER COLOR ===============*/

int					check_color(t_cub *cb, char **line, char *id);

/*=============== MAP ===============*/

void				save_map(t_cub *cb, int height_file);

/*=============== PARAM ===============*/

void				param_full(t_cub *cb);
void				set_param(t_cub *cb);

/*=============== CHECKER MAP ===============*/

void				check_blank_line(t_cub *cb);
void				check_char(t_cub *cb);
void				check_borders(t_cub *cb, int i, int j);
void				check_near_char(t_cub *cb, int i, int j);
void				check_closed_map(t_cub *cb);

/*=============== PLAYER ===============*/

int					ft_isplayer(int c);
void				check_player(t_cub *cb, int *status, int i, int j);

/*=============== COLOR ===============*/

void				save_color(t_cub *cb, char *color, int count, char *id);

/*=============== PARSER ===============*/

void				parse(t_cub *cb, char *arg);

/*=============== RAYTRACER ===============*/

void				raycaster(t_cub *cb);
mlx_texture_t		*get_wall_texture(t_cub *cb, t_raycaster *ray);
void				try_put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, \
					int color);
void				print_pixel(t_cub *cb, t_raycaster *ray, int x, \
					mlx_texture_t *txt);

/*=============== MOVEMENT ===============*/

void				update_player_facing(t_cub *cb);
void				change_pos(t_cub *cb);

/*=============== MLX ===============*/

void				ft_loop_hook(void *param);
void				ft_key_hook(mlx_key_data_t keydata, void *param);

/*=============== DRAW ===============*/

void				try_put_pixel(mlx_image_t *img, uint32_t x, uint32_t y,
						int color);
void				draw_rectangle(mlx_image_t *img, t_vector pos,
						t_vector size, int color);
void				draw_empty_rectangle(mlx_image_t *img, t_vector pos,
						t_vector size, int color);

/*=============== UTILS ===============*/

t_vector			set_vector(double x, double y);
void				free_array(char **array);
int					find_max_len(char **file, int start, int height);
int					is_impediment(char c);

/*=============== UNLEAK ===============*/

void				unleak(t_cub *cb);

/*=============== ERROR ===============*/

void				error(t_cub *cb, int error_num);

/*=============== DRAW ===============*/

#endif