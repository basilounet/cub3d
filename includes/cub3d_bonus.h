/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:30:18 by bvasseur          #+#    #+#             */
/*   Updated: 2024/07/01 15:49:37 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <MLX42/MLX42.h>
# include <libft.h>
# include <math.h>
# include <stdio.h>
# define WIDTH 1000
# define HEIGHT 550
# define MINIMAP_WIDTH 150
# define MINIMAP_HEIGHT 150
# define MINIMAP_SQUARE_SIZE 15
# define ROTATION_SPEED 0.04
# define MOUSE_ROTATION_SPEED 0.0005
# define MOVE_SPEED 0.05
# define PAUSE_MENU_COLOR 0xE0A060E0

# define PAUSE 0b1

# ifndef DEBUG
#  define DEBUG 0
# endif

enum					e_errors
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
	MISSING_BOZO_ERROR = 15,
	MLX_ERROR = 16,
	MAX_ERROR,
};

typedef struct s_cub	t_cub;

typedef struct s_vector
{
	double				x;
	double				y;
}						t_vector;

typedef struct s_button
{
	t_vector			pos;
	t_vector			size;
	t_vector			text_size;
	t_vector			text_offset;
	char				*text;
	char				*txt_name;
	void				(*callback)(t_cub *);
	mlx_texture_t		*txt;
	mlx_image_t			*bg;
	mlx_image_t			*text_img;
}						t_button;

typedef struct s_slider
{
	t_vector			pos;
	t_vector			size;
	t_button			slider;
	t_button			button;
	t_vector			button_offset;
	t_vector			percentage_range;
	void				(*callback)(t_cub *, struct s_slider *);
	int					min;
	int					max;
	int					value;
	double				percentage;
}						t_slider;

typedef struct s_pause
{
	mlx_image_t			*image;
	t_button			*buttons;
	int					buttons_count;
	t_slider			*sliders;
	int					sliders_count;
}						t_pause;

typedef struct s_raycaster
{
	int					step_x;
	int					step_y;
	int					map_x;
	int					map_y;
	t_vector			camera;
	t_vector			raydir;
	t_vector			side_dist;
	t_vector			delta_dist;
	double				perp_wall_dist;
	int					hit;
	int					side;
	int					line_height;
	int					draw_start;
	int					draw_end;
}						t_raycaster;

typedef struct s_player
{
	t_vector			pos;
	t_vector			facing;
	t_vector			plane;
	double				length_plane;
	int					fov;
}						t_player;

typedef struct s_minimap
{
	mlx_image_t			*image;
	double				height;
	double				width;
	double				square_size;
}						t_minimap;

typedef struct s_map
{
	char				**file;
	char				**map;
	char				**param;
	int					*par;
	int					width;
	int					height;
	int					floor_color;
	int					ceiling_color;
	mlx_texture_t		*north_texture;
	mlx_texture_t		*west_texture;
	mlx_texture_t		*south_texture;
	mlx_texture_t		*east_texture;
	mlx_texture_t		*bozo_texture;
}						t_map;

typedef struct s_cub
{
	mlx_t				*mlx;
	mlx_image_t			*image;
	t_map				map;
	t_player			player;
	t_minimap			minimap;
	t_pause				pause;
	int					flags;
}						t_cub;

typedef struct s_bresenham
{
	int					dx;
	int					dy;
	int					sx;
	int					sy;
	int					err;
	int					e2;
}						t_bresenham;

/*=============== CHECKER PARAM ===============*/

int						check_param2(t_cub *cb, int i);

/*=============== CHECKER COLOR ===============*/

int						check_color(t_cub *cb, char **line, char *id);

/*=============== MAP ===============*/

void					save_map(t_cub *cb, int height_file);

/*=============== PARAM ===============*/

void					param_full(t_cub *cb);
void					set_param(t_cub *cb);

/*=============== CHECKER MAP ===============*/

void					check_blank_line(t_cub *cb);
void					check_char(t_cub *cb);
void					check_borders(t_cub *cb, int i, int j);
void					check_near_char(t_cub *cb, int i, int j);
void					check_closed_map(t_cub *cb);

/*=============== PLAYER ===============*/

int						ft_isplayer(int c);
void					check_player(t_cub *cb, int *status, int i, int j);

/*=============== COLOR ===============*/

void					save_color(t_cub *cb, char *color, int count, char *id);

/*=============== PARSER ===============*/

void					parse(t_cub *cb, char *arg);

/*=============== RAYTRACER ===============*/

void					raycaster(t_cub *cb);

/*=============== MOVMENT ===============*/

void					update_player_facing(t_cub *cb);
void					change_pos(t_cub *cb);

/*=============== MLX ===============*/

void					ft_loop_hook(void *param);
void					ft_key_hook(mlx_key_data_t keydata, void *param);
void					ft_mouse_hook(mouse_key_t button, action_t action,
							modifier_key_t mods, void *param);

/*=============== DRAW ===============*/

void					try_put_pixel(mlx_image_t *img, uint32_t x, uint32_t y,
							int color);
void					draw_map(t_cub *cb, t_minimap mm);
void					draw_rectangle(mlx_image_t *img, t_vector pos,
							t_vector size, int color);
void					draw_empty_rectangle(mlx_image_t *img, t_vector pos,
							t_vector size, int color);
void					draw_triangle(mlx_image_t *img, t_vector pos,
							t_vector facing, int color);
void					draw_line(mlx_image_t *img, t_vector p0, t_vector p1,
							int color);

/*=============== PAUSE ===============*/

void					create_pause_screen(t_cub *cb);
void					change_pause_state(t_cub *cb);
int						is_in_button(t_cub *cb, t_vector pos, t_vector size);
void					pause_button_press(t_cub *cb);
void					place_buttons(t_cub *cb);

/*=============== CALLBACKS ===============*/

void					exit_callback(t_cub *cb);
void					scale_1_3(t_cub *cb);
void					scale_2_3(t_cub *cb);
void					scale_1_1(t_cub *cb);

/*=============== UTILS ===============*/

t_vector				set_vector(double x, double y);
void					free_array(char **array);
int						find_max_len(char **file, int start, int height);
t_vector				multiply_vector(t_vector vector, double multiplier);

/*=============== UNLEAK ===============*/

void					unleak(t_cub *cb);
void					*ft_delete_textures(int nb, ...);
void					*ft_delete_images(t_cub *cb, int nb, ...);

/*=============== ERROR ===============*/

void					error(t_cub *cb, int error_num);

#endif