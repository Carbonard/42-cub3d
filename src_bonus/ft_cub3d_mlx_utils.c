/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_mlx_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 23:57:56 by rselva-2          #+#    #+#             */
/*   Updated: 2026/09/08 14:28:53 by rselva-2         ###   ########.fr       */
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
	dst = image->addr + (y * image->line_size + x * (image->bpp / 8));
	*(unsigned int *) dst = color;
}

unsigned int	get_pixel(const t_mlx_image *image, int x, int y)
{
	char	*src;

	if (x < 0 || x > image->width || y < 0 || y > image->height)
	{
		// printf("Debug: Trying to read in (%d,%d)\nThe limits are (%d, %d)\n",
		// 	x, y, image->width, image->height);
		// sleep(5);
		return (rgb(0, 0, 0));
	}
	src = image->addr + (y * image->line_size + x * (image->bpp / 8));
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
	image->img = mlx_xpm_file_to_image(ctx->mlx, file_name,
			&image->width, &image->height);
	if (!image->img)
	{
		ft_putstr_fd("error\n", 2);
		perror(file_name);
		close_game(ctx, C3D_BAD_FILE);
	}
	get_img_data(image);
}

void	safe_close_image(void *mlx, t_mlx_image *image)
{
	if (image->img)
	{
		mlx_destroy_image(mlx, image->img);
		image->img = NULL;
	}
}
