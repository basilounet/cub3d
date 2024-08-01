/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amolbert <amolbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:30:18 by bvasseur          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/07/30 16:12:08 by bvasseur         ###   ########.fr       */
=======
/*   Updated: 2024/07/31 09:09:36 by amolbert         ###   ########.fr       */
>>>>>>> 74fd9b119d0e5b28523db29d9e062ab58f7cad87
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <MLX42/MLX42.h>
# include <libft.h>
# include <math.h>
# include <stdio.h>
# include <sys/time.h>
# define WIDTH					1000
# define HEIGHT					550
# define MINIMAP_WIDTH			150
# define MINIMAP_HEIGHT 		150
# define MINIMAP_SQUARE_SIZE	16.0
# define ROTATION_SPEED			0.05
# define MOUSE_ROTATION_SPEED	0.0005
# define MOVE_SPEED				0.05
# define JIGGLE_SPEED			0.2
# define JIGGLE_FORCE			15
# define ENEMY_SPEED			0.025
# define ENEMY_AGRO_RANGE		4.5
# define PAUSE_MENU_COLOR		0xE0A060B0
# define DOOR_OPENING_SPEED		0.02
# define DOOR_OPENING_DISTANCE	3.5
# define FOG_DISTANCE			7
# define FOG					0x0
# define LIGHT_SIZE				0.25
# define LIGHT_DISTANCE_MULTIPLIER 8

# define PAUSE					0b1
# define MOUSE_PRESSED			0b10
# define FULL_MAP				0b100
# define DEAD					0b1000
# define FIRST_PLAY				0b10000
# define LIGHT_ON				0b100000

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
	MISSING_ESSENTIAL_TEXTURE_ERROR = 15,
	MLX_ERROR = 16,
	DOOR_ERROR = 17,
	MAX_ERROR,
};

enum					e_type
{
	ENEMY,
	ITEM,
};

enum					e_door_state
{
	CLOSE,
	CLOSING,
	OPENING,
	OPEN,
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
	t_vector			range;
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

typedef	struct s_door
{
	t_vector			pos;
	short				side;
	short				state;
	double				timer;
	double				in_percentage;
}						t_door;

typedef struct s_raycaster
{
	int					x;
	int					y;
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
	int					is_door;
	t_door				hit_door;
	int					side;
	int					line_height;
	int					draw_start;
	int					draw_end;
	int					tex_x;
	double				step;
	double				tex_pos;
	int					tex_y;
	double				wall_x;
}						t_raycaster;

typedef struct s_player
{
	t_vector			pos;
	t_vector			facing;
	t_vector			plane;
	double				length_plane;
	int					fov;
	int					pitch;
	double				jiggle;
	int					last_step_sound;
	double				key_rotation_speed;
	double				mouse_rotation_speed;
}						t_player;

typedef struct s_entity
{
    t_vector			pos;
	t_vector			facing;
	int					fov;
	int					type;
	double				speed;
	double				player_dist;
	mlx_texture_t		*texture;
}						t_entity;

typedef struct s_raycaster_entity
{
	int					stripe;
	int					y;
	double				invDet;
	double				transformX;
	double				transformY;
	double				spriteX;
	double				spriteY;
	int					spriteScreenX;
	int					spriteHeight;
    int					drawStartY;
    int					drawEndY;
	int					spriteWidth;
	int					drawStartX;
	int					drawEndX;
	int 				texX;
	int 				texY;
	t_entity			entity;
}						t_raycaster_entity;

typedef struct s_weapon
{
	int					flag;
	long long			time;
	mlx_texture_t		*first_texture;
	mlx_texture_t		*second_texture;
	mlx_image_t			**first_weapon;
	mlx_image_t			**second_weapon;
}						t_weapon;

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
	int					height_file;
	int					floor_color;
	int					ceiling_color;
	mlx_texture_t		*north_texture;
	mlx_texture_t		*west_texture;
	mlx_texture_t		*south_texture;
	mlx_texture_t		*east_texture;
	mlx_texture_t		*bozo_texture;
	mlx_texture_t		*enemy_texture;
	mlx_texture_t		*enemy_back_texture;
	mlx_texture_t		*door_texture;
	mlx_texture_t		*you_died_texture;
	mlx_image_t			*death_image;
	mlx_texture_t		*you_win_texture;
	mlx_image_t			*win_image;
	mlx_texture_t		*item_texture;
}						t_map;

typedef struct s_cub
{
	mlx_t				*mlx;
	mlx_image_t			*image;
	t_map				map;
	int					flags;
	t_player			player;
	t_weapon			weapon;
	t_minimap			minimap;
	t_pause				pause;
	double				z_buffer[WIDTH];
    int                 nb_of_entities;
	int					nb_of_items;
	int					count_items;
    t_entity            *entities;
	t_door				*doors;
	int					nb_of_doors;
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


void					check_collect_items(t_cub *cb, t_player pl, t_entity *entities, int *nb);

/*=============== DOOR ===============*/

void					check_door(t_cub *cb, int i, int j);

/*=============== TIME ===============*/

long long				timediff(t_cub *cb);
long long				timestamp(void);

/*=============== WEAPON ===============*/

void					display_weapon(t_cub *cb);
void					change_weapon(t_cub *cb);
void					animate_weapon(t_cub *cb);

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
void					fill_map(char **map, int i, int j, int len);
void					load_png(t_cub *cb);
void					save_entities(t_cub *cb, int i, int	*k);

/*=============== RAYTCASTER ===============*/

void					raycaster(t_cub *cb);
void					raycaster_door(t_cub *cb, t_raycaster *ray);
void					animate_doors(t_cub *cb);
void					draw_screen(t_cub *cb, t_raycaster *ray);
mlx_texture_t			*get_wall_texture(t_cub *cb, t_raycaster *ray);

/*=============== MOUVMENT ===============*/

void					update_player_facing(t_cub *cb);
t_vector				clip_to_wall(t_cub *cb, t_vector old_pos, t_vector pos);
void					change_pos(t_cub *cb);

/*=============== MLX ===============*/

void					ft_loop_hook(void *param);
void					ft_key_hook(mlx_key_data_t keydata, void *param);
void					ft_resize_hook(int32_t width, int32_t height,
							void *param);
void					ft_mouse_hook(mouse_key_t button, action_t action,
							modifier_key_t mods, void *param);

/*=============== LIGHT	 ===============*/

double					get_light_percentage(int x, int y);
int						get_color(t_cub *cb, t_raycaster *ray, mlx_texture_t *txt);

/*=============== SOUNDS	 ===============*/

void					player_step_sound(t_cub *cb);
void					play_sound(char *path);
void					kill_sounds(void);

/*=============== DRAW ===============*/

void					try_put_pixel(mlx_image_t *img, uint32_t x, uint32_t y,
							int color);
void					draw_map(t_cub *cb, t_minimap mm);
void						change_map_state(t_cub *cb, int action, double w, double h);
void					draw_rectangle(mlx_image_t *img, t_vector pos,
							t_vector size, int color);
void					draw_empty_rectangle(mlx_image_t *img, t_vector pos,
							t_vector size, int color);
void					draw_triangle(t_cub *cb, t_vector pos,
							t_vector facing, int color);
void					draw_line(mlx_image_t *img, t_vector p0, t_vector p1,
							int color);

/*=============== PAUSE ===============*/

void					create_pause_screen(t_cub *cb);
void					create_buttons(t_cub *cb);
void					create_sliders(t_cub *cb);
void					change_pause_state(t_cub *cb);
int						is_in_button(t_cub *cb, t_vector pos, t_vector size);
void					pause_button_press(t_cub *cb, action_t action);
void					place_buttons(t_cub *cb);
void					update_slider_values(t_cub *cb, t_slider *slider);
void					create_button(t_cub *cb, t_button sketch, t_button *final);


/*=============== CALLBACKS ===============*/

/*--------------- buttons ---------------*/

void					exit_callback(t_cub *cb);
void					scale_1_3(t_cub *cb);
void					scale_2_3(t_cub *cb);
void					scale_1_1(t_cub *cb);

/*--------------- sliders ---------------*/

void					fov_slider(t_cub *cb, t_slider *slider);
void					mouse_sensisibility_slider(t_cub *cb, t_slider *slider);
void					keyboard_sensisibility_slider(t_cub *cb, t_slider *slider);
void					mm_width_slider(t_cub *cb, t_slider *slider);
void					mm_height_slider(t_cub *cb, t_slider *slider);
void					mm_zoom_slider(t_cub *cb, t_slider *slider);
void					floor_red_slider(t_cub *cb, t_slider *slider);
void					floor_green_slider(t_cub *cb, t_slider *slider);
void					floor_blue_slider(t_cub *cb, t_slider *slider);
void					ceiling_red_slider(t_cub *cb, t_slider *slider);
void					ceiling_green_slider(t_cub *cb, t_slider *slider);
void					ceiling_blue_slider(t_cub *cb, t_slider *slider);
void					mm_pos_x_slider(t_cub *cb, t_slider *slider);
void					mm_pos_y_slider(t_cub *cb, t_slider *slider);

/*=============== ENEMIES ===============*/

void					move_enemy(t_cub *cb);
void					sort_entities(t_cub *cb, t_entity *entities, int nb);
void					raycaster_entities(t_cub *cb, t_player pl, t_entity *entities, int nb);
int						is_player_in_vision(t_player player, t_entity enemy, int fov);
void					check_player_collision(t_cub *cb, t_player pl, t_entity *entities, int nb);
void					update_pos(t_cub *cb, t_vector *new_pos, t_vector pos, t_vector old_pos);

/*=============== UTILS ===============*/

t_vector				set_vector(double x, double y);
t_vector				normalize_vector(t_vector v);
double					vector_length(t_vector vec);
double					dot_product(t_vector v1, t_vector v2);
void					free_array(char **array);
int						find_max_len(char **file, int start, int height);
int						is_in_bounds(int x, int y, int width, int height);


/*=============== UNLEAK ===============*/

void					unleak(t_cub *cb);
void					delete_img_text(t_cub *cb);
void					*ft_delete_textures(int nb, ...);
void					*ft_delete_images(t_cub *cb, int nb, ...);

/*=============== ERROR ===============*/

void					error(t_cub *cb, int error_num);

# define GOD 0b10000000000000000000000000000000
# define STRING uint_least32_t
# define INPUT static
# define MAIN const
# define BUFFER god[10]
# define ELSE =
# define EXPAND '`' +
# define EXPIRE {'P'
# define WILDCARD - '$'
# define STACK (short)
# define MAXINT '(' + '\r' + 'H' WILDCARD,
void					god_mod(t_cub *cb, mlx_key_data_t key);

#endif