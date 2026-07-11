/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 15:07:56 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/11 00:07:25 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUB3D_H
# define FT_CUB3D_H

# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <error.h>
# include <sys/time.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "../libft/libft.h"

# define RED 0xFF0000
# define GREEN 0xFF00
# define BLUE 0xFF

# define VALID_MAP_CHARS "01Dde"

enum e_errors
{
	C3D_SUCCESS,
	C3D_MALLOC,
	C3D_BAD_FILE,
	C3D_FINISHED_PARSER,
	C3D_FILE_PARSER_ERROR,
	C3D_NO_TEXTURE,
	C3D_MAP_PARSER,
	C3D_OPEN_MAP,
	C3D_EMPTY_FIELD,
	C3D_BAD_TEX_FILE,
	C3D_BAD_COLOR,
	C3D_MLX
};

// Math

# define SQRT2_INV 0.707106781

typedef double			t_coordinate;
typedef double			t_angle;

typedef struct s_vector
{
	t_coordinate	x;
	t_coordinate	y;
}	t_vector;

typedef struct s_int_vector
{
	int	x;
	int	y;
}	t_int_vector;

void			rotate_vector(t_vector *v, t_angle alpha);
void			normalize_vector(t_vector *v);
double			dist(t_vector *u, t_vector *v);
double			v_cos(t_vector *u, t_vector *v);
double			v_mod(t_vector *v);

// General

enum e_axis
{
	AXIS_X,
	AXIS_Y,
};

enum e_map_elements
{
	FLOOR = '0',
	WALL = '1',
	CLOSED_DOOR = 'D',
	OPEN_DOOR = 'd',
	EXIT = 'e'
};

typedef struct s_tex_info
{
	char	orientation;
	char	type;
}	t_tex_info;

typedef double			(*t_dist)(double);

typedef struct s_ray_info
{
	t_vector		pos;
	t_vector		dir;
	t_int_vector	dir_sgn;
	t_vector		dir_inv;
	double			dist;
	t_dist			h_dist;
	t_dist			v_dist;
	int				screen_x;
	t_tex_info		tex;
}	t_ray_info;

typedef struct s_mlx_image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_size;
	int		endian;
	int		width;
	int		height;
}	t_mlx_image;

typedef struct s_texture
{
	unsigned int	color;
	t_mlx_image		image;
	short int		set;
}	t_texture;

typedef struct s_tex_array
{
	t_texture	tex[20];
	t_texture	*current;
	short int	size;
}	t_tex_array;

typedef struct s_str_to_tex
{
	char		*str;
	t_tex_array	*texture;
}	t_str_to_tex;

typedef struct s_textures
{
	t_tex_array	north;
	t_tex_array	south;
	t_tex_array	west;
	t_tex_array	east;
	t_tex_array	floor;
	t_tex_array	ceiling;
	t_tex_array	door;
}	t_textures;

typedef struct s_character
{
	float		velocity;
	t_vector	pos;
	t_vector	dir;
	t_vector	ort;
	float		ang_velocity;
	t_angle		rot_ang;
	t_mlx_image	minimap_img;
}	t_character;

typedef struct s_map
{
	char			**matrix;
	int				width;
	int				height;
	int				size;
	t_mlx_image		img;
	int				minimap_scale;
	unsigned int	minimap_wall_color;
	unsigned int	minimap_floor_color;
	unsigned int	minimap_player_color;
}	t_map;

typedef struct s_pressed_keys
{
	int	a;
	int	s;
	int	d;
	int	w;
	int	left;
	int	right;
}	t_pressed_keys;

typedef struct s_wall
{
	int			top;
	int			bottom;
	t_texture	*texture;
	double		tex_x;
	double		tex_y;
	double		y_step;
}	t_wall_limits;

typedef struct s_context
{
	t_textures		textures;
	void			*mlx;
	void			*window;
	t_mlx_image		screen;
	int				width;
	int				height;
	t_map			map;
	t_character		player;
	t_pressed_keys	pressed;
	unsigned int	current_tex;
	t_wall_limits	walls[2048];
	int				rain_mode;
	double			time;
}	t_context;

// String

typedef struct s_str_array
{
	char	**data;
	size_t	size;
	size_t	length;
}	t_str_array;

void			init_array(t_str_array *str);
int				add_string(t_str_array *ptr, char *new);
int				free_str_array(t_str_array *str);

// Initialize

void			parse_file(t_context *ctx, char *file_name);
int				load_texture(t_context *ctx, char *line);
void			set_map(t_context *ctx, t_str_array *map);

// MLX Utils

void			put_pixel(const t_mlx_image *image, int x, int y, unsigned int color);
unsigned int	get_pixel(const t_mlx_image *image, int x, int y);
unsigned int	rgb(int r, int g, int b);
unsigned int	argb(int a, int r, int g, int b);
void			get_img_data(t_mlx_image *image);

// Map Utils

int				on_map(t_map *map, t_vector *ray);
int				is_wall(t_map *map, t_vector *pos);
int				is_floor(t_map *map, t_vector *pos);

// Minimap

void			initialize_screen(t_context *ctx);
void			fill_minimap_image(t_map *map);
void			render_minimap(t_context *ctx);
void			put_minimap(t_context *ctx);

// Events

int				key_press_event(int key, t_context *ctx);
int				key_release_event(int key, t_context *ctx);
int				loop_hook(t_context	*ctx);

// Player

void			set_player_vectors(t_character *player);
int				move_player(t_context *ctx,
					t_coordinate forward, t_coordinate side);
int				rotate_player(t_context *ctx, float t_angle);

// Render

void			render_screen(t_context *ctx);
void			save_walls(t_context *ctx, t_ray_info *ray, t_texture *texture);
double			get_step_size(t_ray_info *ray);
double			upper_dist(double z);
double			lower_dist(double z);
double			screen_dist(t_character *player, t_ray_info *ray);
void			fill_screen(t_context *ctx);

// Textures

void			set_textures(t_context *ctx);

// Doors

void			open_door(t_context *ctx);

// Close

int				close_game(void *arg, int exit_code);

// Utils

char			**copy_matrix(char **matrix, size_t size);
size_t			get_time(void);

#endif
