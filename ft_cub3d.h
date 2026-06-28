/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 15:07:56 by rselva-2          #+#    #+#             */
/*   Updated: 2026/06/28 15:21:30 by rselva-2         ###   ########.fr       */
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


// Math

typedef float coordinate;

typedef float angle;

typedef struct	s_vector
{
	coordinate	x;
	coordinate	y;
}	t_vector;

void	rotate_vector(t_vector *v, angle alpha);

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

typedef struct s_vistuals
{
	t_mlx_image	north;
	t_mlx_image	south;
	t_mlx_image	west;
	t_mlx_image	east;
	int			floor;
	int			ceil;
}	t_visuals;

typedef struct s_character
{
	t_vector	pos;
	t_vector	dir;
	t_vector	ort;
	angle		rot_ang;
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

typedef struct s_context
{
	t_visuals	visuals;
	void		*mlx;
	void		*window;
	int			width;
	int			height;
	t_map		map;
	t_character	player;
}	t_context;

// String

typedef	struct s_str_array
{
	char	**data;
	size_t	size;
	size_t	length;
}	t_str_array;

void	init_string(t_str_array *str);
int		string_pushback(t_str_array *ptr, char *new);
int		string_delete(t_str_array *str);

// Utils

void	put_pixel(t_mlx_image *image, int x, int y, int color);
unsigned int	rgb(int r, int g, int b);
void	get_img_data(t_mlx_image *image);

// Minimap

void	initialize_minimap(t_context *ctx);
void	render_minimap(t_context *ctx);

// Events

int	key_press_event(int key, t_context *ctx);

// Player

void	set_player_vectors(t_character *player);
void	move_player(t_context *ctx, coordinate forward, coordinate side);
void	rotate_player(t_context *ctx, float angle);

// Close

void	close_images(t_context *ctx);
int		close_window(void *arg);

#endif
