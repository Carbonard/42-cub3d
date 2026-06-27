/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 15:07:56 by rselva-2          #+#    #+#             */
/*   Updated: 2026/06/27 22:16:48 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <error.h>
# include <sys/time.h>
# include "./minilibx-linux/mlx.h"
# include "./minilibx-linux/mlx_int.h"
# include "./libft/libft.h"

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
	int		pos_x;
	int		pos_y;
	int		dir_x;
	int		dir_y;
}	t_character;

typedef struct s_map
{
	char	**matrix;
	int		width;
	int		height;
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




#endif
