/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 15:07:56 by rselva-2          #+#    #+#             */
/*   Updated: 2026/06/29 16:30:15 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <error.h>
# include <sys/time.h>
# include <math.h>
# include "./minilibx-linux/mlx.h"
# include "./minilibx-linux/mlx_int.h"
# include "./libft/libft.h"

enum e_errors
{
	C3D_SUCCESS,
	C3D_MALLOC,
	C3D_BAD_FILE,
	C3D_FINISHED_PARSER,
	C3D_FILE_PARSER_ERROR,
	C3D_MAP_PARSER,
	C3D_OPEN_MAP
};

// Math

typedef float t_coordinate;

typedef float t_angle;

typedef struct	s_vector
{
	t_coordinate	x;
	t_coordinate	y;
}	t_vector;

void	rotate_vector(t_vector *v, t_angle alpha);

// General

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

typedef struct s_textures
{
	t_mlx_image	north;
	t_mlx_image	south;
	t_mlx_image	west;
	t_mlx_image	east;
	int			floor;
	int			ceil;
}	t_textures;

typedef struct s_character
{
	t_vector	pos;
	t_vector	dir;
	t_vector	ort;
	t_angle		rot_ang;
	t_mlx_image	minimap_img;
}	t_character;

typedef struct s_map
{
	char		**matrix;
	int			width;
	int			height;
	int			size;
	t_mlx_image	img;
	int			scale;
}	t_map;

typedef struct	s_pressed_keys
{
	int	a;
	int	s;
	int	d;
	int	w;
	int	left;
	int	right;
}	t_pressed_keys;


typedef struct s_context
{
	t_textures		textures;
	void			*mlx;
	void			*window;
	int				width;
	int				height;
	t_map			map;
	t_character		player;
	t_pressed_keys	pressed;
}	t_context;

// String

typedef	struct s_str_array
{
	char	**data;
	size_t	size;
	size_t	length;
}	t_str_array;

void	init_array(t_str_array *str);
int		add_string(t_str_array *ptr, char *new);
int		free_str_array(t_str_array *str);

// Initialize

void	read_file(t_context *ctx, char *file_name);
void	set_map(t_context *ctx, t_str_array *map);

// MLX Utils

void	put_pixel(t_mlx_image *image, int x, int y, int color);
unsigned int	rgb(int r, int g, int b);
void	get_img_data(t_mlx_image *image);

// Minimap

void	initialize_minimap(t_context *ctx);
void	render_minimap(t_context *ctx);

// Events

int	key_press_event(int key, t_context *ctx);
int	key_release_event(int key, t_context *ctx);
int	loop_hook(t_context	*ctx);

// Player

void	set_player_vectors(t_character *player);
int		move_player(t_context *ctx, t_coordinate forward, t_coordinate side);
int		rotate_player(t_context *ctx, float t_angle);

// Close

void	close_images(t_context *ctx);
int		close_game(void *arg, int exit_code);

// Utils

char	**copy_matrix(char **matrix, size_t size);
size_t	get_time(void);

#endif
