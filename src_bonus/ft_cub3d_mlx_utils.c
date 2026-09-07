/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_mlx_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 23:57:56 by rselva-2          #+#    #+#             */
/*   Updated: 2026/09/07 15:28:43 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	put_pixel(const t_mlx_image *image, int x, int y, t_color color)
{
	char	*dst;

	if (x < 0 || x > image->width || y < 0 || y > image->height)
	{
		// printf("Debug: Trying to draw in (%d,%d)\nThe limits are (%d, %d)\n",
		// 	x, y, image->width, image->height);
		// sleep(5);
		return ;
	}
	// printf("Debug: Drawing in (%d,%d)\nThe limits are (%d, %d)\n",
	// 		x, y, image->width, image->height);
	dst = image->addr + (y * image->line_size + x * (image->bpp / 8));
	*(unsigned int *) dst = color;
	// printf("fine \n");
}

unsigned int	get_pixel(const t_mlx_image *image, int x, int y)
{
	char	*src;

	if (x < 0 || x > image->width || y < 0 || y > image->height)
	{
		// printf("Debug: Trying to read in (%d,%d)\nThe limits are (%d, %d)\n",
		// 	x, y, image->width, image->height);
		// sleep(5);
		return (rgb(255, 0, 0));
	}
	src = image->addr + (y * image->line_size + x * (image->bpp / 8));
	// printf("Debug: copying in %p (%d,%d)\nThe limits are (%d, %d)\n",
	// 		src, x, y, image->width, image->height);
	// unsigned int c = *(unsigned int *) src;
	// printf("fine\n");
	// return (c);
	return (*(unsigned int *) src);
}

void	get_img_data(t_mlx_image *image)
{
	image->addr = mlx_get_data_addr(
			image->img,
			&image->bpp,
			&image->line_size,
			&image->endian);
}

void	read_xpm(t_context *ctx, t_mlx_image *image, char *file_name)
{
	image->img = mlx_xpm_file_to_image(ctx->mlx, file_name, &image->width, &image->height);
	if (!image->img)
	{
		ft_putstr_fd("error\n", 2);
		perror(file_name);
		close_game(ctx, C3D_BAD_FILE);
	}
	get_img_data(image);
}
