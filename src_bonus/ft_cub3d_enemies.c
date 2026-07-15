/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_enemies.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 02:18:32 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/12 19:58:07 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

#define TRANSPARENT 0xFF00FF

void	convert(t_mlx_image *image)
{
	int				j;
	int				i;
	unsigned int	color;

	j = 0;
	while (j < image->width)
	{
		i = 0;
		while (i < image->height)
		{
			color = get_pixel(image, i, j);
			if (color != TRANSPARENT)
				put_pixel(image, i, j, color | 0xFF000000);
			else
				put_pixel(image, i, j, 0);
			i++;
		}
		j++;
	}
}

void	convert_transparencies(t_tex_array *texture)
{
	int	i;

	i = 0;
	while (i < texture->size)
	{
		convert(&texture[i].tex->image);
		i++;
	}
}
