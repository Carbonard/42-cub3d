/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_put_screen.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 20:07:12 by rselva-2          #+#    #+#             */
/*   Updated: 2026/09/11 21:12:36 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

static void	put_info_square(t_context *ctx, int x, int y)
{
	int				i;
	int				j;
	int				width;
	int				height;
	unsigned int	color;

	width = 65;
	height = 40;
	color = rgb(200, 200, 200);
	i = 0;
	while (i < width)
	{
		j = 0;
		while (j < height)
		{
			put_pixel(
				&ctx->real_screen,
				x + i,
				y + j,
				color);
			j++;
		}
		i++;
	}
}

void	put_screen(t_context *ctx)
{
	char			*aux;
	t_int_vector	screen_size;

	screen_size.x = ctx->width * ctx->pix_size;
	screen_size.y = ctx->height * ctx->pix_size;
	resize_screen(ctx);
	put_info_square(ctx, screen_size.x - 142, screen_size.y - 63);
	mlx_put_image_to_window(ctx->mlx, ctx->window, ctx->real_screen.img, 0, 0);
	aux = ft_itoa(ctx->time / 10);
	mlx_string_put(ctx->mlx, ctx->window,
		screen_size.x - 137, screen_size.y - 50, rgb(10, 10, 10), "Time: ");
	mlx_string_put(ctx->mlx, ctx->window,
		screen_size.x - 100, screen_size.y - 50, rgb(10, 10, 10), aux);
	free(aux);
	aux = ft_itoa(ctx->real_fps);
	mlx_string_put(ctx->mlx, ctx->window,
		screen_size.x - 130, screen_size.y - 30, rgb(10, 10, 100), "FPS: ");
	mlx_string_put(ctx->mlx, ctx->window,
		screen_size.x - 100, screen_size.y - 30, rgb(10, 10, 100), aux);
	free(aux);
}
