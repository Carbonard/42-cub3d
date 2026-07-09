/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_mlx_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 23:57:56 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/09 18:04:31 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	put_pixel(t_mlx_image *image, int x, int y, unsigned int color)
{
	char	*dst;

	// if (x < 0 || x > image->width || y < 0 || y > image->height)
	// {
	// 	printf("Debug: Trying to print in (%d,%d)\nThe limits are (%d, %d)\n",
	// 		x, y, image->width, image->height);
	// 	return ;
	// }
	dst = image->addr + (y * image->line_size + x * (image->bpp >> 3));
	*(unsigned int *) dst = color;
}

unsigned int	get_pixel(t_mlx_image *image, int x, int y)
{
	char	*src;

	// if (x < 0 || x > image->width || y < 0 || y > image->height)
	// {
	// 	printf("Debug: Trying to read in (%d,%d)\nThe limits are (%d, %d)\n",
	// 		x, y, image->width, image->height);
	// 	return (rgb(255, 0, 0));
	// }
	src = image->addr + (y * image->line_size + x * (image->bpp >> 3));
	return (*(unsigned int *) src);
}

unsigned int	rgb(int r, int g, int b)
{
	return ((r << 16) + (g << 8) + b);
}

unsigned int	argb(int a, int r, int g, int b)
{
	return ((a << 24) + (r << 16) + (g << 8) + b);
}

void	get_img_data(t_mlx_image *image)
{
	image->addr = mlx_get_data_addr(
			image->img,
			&image->bpp,
			&image->line_size,
			&image->endian);
}
