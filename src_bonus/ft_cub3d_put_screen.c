/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_put_screen.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 20:07:12 by rselva-2          #+#    #+#             */
/*   Updated: 2026/09/12 00:27:46 by rselva-2         ###   ########.fr       */
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

static void	time(int slot, int step)
{
	static size_t	t[10] = {0};
	static size_t	total_time[10] = {0};
	static size_t	cnt[10] = {0};
	static int		first_time[10] = {0};

	if (step == 1)
	{
		t[slot] = get_time();
	}
	else
	{
		cnt[slot]++;
		total_time[slot] += get_time() - t[slot];
		if (cnt[slot] % 100 == 0)
		{
			printf("%d: time mean after %lu iterations: %lf\n", slot, cnt[slot],
				(double)total_time[slot] / cnt[slot]);
			if (!first_time[slot])
			{
				cnt[slot] = 0;
				total_time[slot] = 0;
				first_time[slot] = 1;
			}
		}
	}
}

void	put_screen(t_context *ctx)
{
	char			*aux;
	char			text[100];
	t_int_vector	screen_size;

	screen_size.x = ctx->width * ctx->pix_size;
	screen_size.y = ctx->height * ctx->pix_size;
	time(8, 1);
	resize_screen(ctx);
	time(8, 2);
	time(9, 1);
	put_info_square(ctx, screen_size.x - 142, screen_size.y - 203);
	mlx_put_image_to_window(ctx->mlx, ctx->window, ctx->real_screen.img, 0, 0);
	aux = ft_itoa(ctx->time / 10);
	ft_strlcpy(text, "Time: ", 100);
	ft_strlcat(text, aux, 100);
	free(aux);
	mlx_string_put(ctx->mlx, ctx->window,
		screen_size.x - 137, screen_size.y - 190, rgb(10, 10, 10), text);
	aux = ft_itoa(ctx->real_fps);
	ft_strlcpy(text, "FPS:  ", 100);
	ft_strlcat(text, aux, 100);
	free(aux);
	mlx_string_put(ctx->mlx, ctx->window,
		screen_size.x - 137, screen_size.y - 170, rgb(10, 10, 10), text);
	time(9, 2);
}

// void	put_screen(t_context *ctx)
// {
// 	char			*aux;
// 	t_int_vector	screen_size;

// 	screen_size.x = ctx->width * ctx->pix_size;
// 	screen_size.y = ctx->height * ctx->pix_size;
// 	resize_screen(ctx);
// 	put_info_square(ctx, screen_size.x - 142, screen_size.y - 203);
// 	mlx_put_image_to_window(ctx->mlx, ctx->window, ctx->real_screen.img, 0, 0);
// 	aux = ft_itoa(ctx->time / 10);
// 	mlx_string_put(ctx->mlx, ctx->window,
// 		screen_size.x - 137, screen_size.y - 190, rgb(10, 10, 10), "Time: ");
// 	mlx_string_put(ctx->mlx, ctx->window,
// 		screen_size.x - 100, screen_size.y - 190, rgb(10, 10, 10), aux);
// 	free(aux);
// 	aux = ft_itoa(ctx->real_fps);
// 	mlx_string_put(ctx->mlx, ctx->window,
// 		screen_size.x - 130, screen_size.y - 170, rgb(10, 10, 100), "FPS: ");
// 	mlx_string_put(ctx->mlx, ctx->window,
// 		screen_size.x - 100, screen_size.y - 170, rgb(10, 10, 100), aux);
// 	free(aux);
// }
