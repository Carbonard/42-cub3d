/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_mlx_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 23:57:56 by rselva-2          #+#    #+#             */
/*   Updated: 2026/06/30 19:51:54 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	put_pixel(t_mlx_image *image, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > image->width || y < 0 || y > image->height)
	{
		printf("Oh no...\nTrying to print inf (%d,%d)\nThe limits are (%d, %d)\n", x, y, image->width, image->height);
		return ;
	}
	dst = image->addr + (y * image->line_size + x * (image->bpp / 8));
	*(unsigned int*)dst = color;
}

unsigned int	rgb(int r, int g, int b)
{
	return ((255 << 24) + (r << 16) + (g << 8) + b);
}

void	get_img_data(t_mlx_image *image)
{
	image->addr = mlx_get_data_addr(
		image->img,
		&image->bpp,
		&image->line_size,
		&image->endian);
}
