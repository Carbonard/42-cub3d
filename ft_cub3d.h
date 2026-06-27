/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 15:07:56 by rselva-2          #+#    #+#             */
/*   Updated: 2026/06/27 15:59:27 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <error.h>
# include <sys/time.h>

typedef struct s_mlx_iamge
{
	void	*img;
	int		width;
	int		height;
}	t_mlx_image;

typedef struct s_vistuals
{
	t_mlx_image	NO;
	t_mlx_image	SO;
	t_mlx_image	WE;
	t_mlx_image	EA;
	int			F;
	int			C;
}	t_visuals;

// String

typedef	struct s_string
{
	char	*data;
	size_t	size;
	size_t	length;
}	t_string;

void	init_string(t_string *str);
int		string_pushback(t_string *str, char c);
int		string_delete(t_string *str);




#endif
