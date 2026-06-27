/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 15:07:56 by rselva-2          #+#    #+#             */
/*   Updated: 2026/06/27 20:05:38 by rselva-2         ###   ########.fr       */
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

typedef struct s_mlx_iamge
{
	void	*img;
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

typedef struct s_context
{
	t_visuals	visuals;
	void		*mlx;
	void		*window;
	int			width;
	int			height;
}	t_context;

// String

typedef	struct s_string
{
	char	**data;
	size_t	size;
	size_t	length;
}	t_string;

void	init_string(t_string *str);
int		string_pushback(t_string *ptr, char *new);
int		string_delete(t_string *str);




#endif
