/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_menu_config.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 01:58:21 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/29 05:46:20 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

static int	put_left_aligned_scaled_image(t_context *ctx, t_mlx_image *image, int height, int y0)
{
	double	factor;
	int		x0;
	int		x;
	int		y;

	factor = (double)image->height / height;
	x0 = ctx->width * 0.4 - image->width / factor;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < image->width * height / image->height)
		{
			put_pixel(&ctx->screen, x0 + x, y0 + y,
				// get_pixel(image, x * factor, y * factor));
				merge_colors(
					get_pixel(&ctx->screen,
						x0 + x, y0 + y),
					get_pixel(image, x * factor, y * factor)));
			x++;
		}
		y++;
	}
	return (y);
}

void	put_circle(t_mlx_image *image, int x, int y, unsigned int color)
{
	int	i;
	int	j;
	int	rad;

	rad = 6;
	i = - rad;
	while (i <= rad)
	{
		j = - rad;
		while (j <= + rad)
		{
			if (i * i + j * j < rad * rad)
				put_pixel(image, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	bar_min_max(t_context *ctx, float percentage, int y0, unsigned int color)
{
	int	i;
	int	start;
	int	end;
	int	y;

	start = ctx->width * 0.6;
	end = ctx->width * 0.9;
	y = y0-1;
	while (y <= y0 + 1)
	{
		i = start;
		while (i < end)
		{
			put_pixel(&ctx->screen, i, y, color);
			i++;
		}
		y++;
	}
	put_circle(&ctx->screen,
		percentage * (end - start) + start, y0, color);
}

static void	put_buttons(t_context *ctx, t_config_button *buttons, int size, int focus, int start)
{
	int	i;
	int	height;
	int	separation;

	separation = 20;
	height = fmin((ctx->height - start) / size - separation, ctx->height * 0.1);
	i = 0;
	while (i < size - 1)
	{
		if (i == focus)
		{
			put_left_aligned_scaled_image(ctx, &buttons[i].focus_image, height, start + i * (height + separation));
			bar_min_max(ctx, (float)buttons[i].config->current / buttons[i].config->max, start + i * (height + separation) + height * 0.5, rgb(128, 128, 221));
		}
		else
		{
			put_left_aligned_scaled_image(ctx, &buttons[i].image, height, start + i * (height + separation));
			bar_min_max(ctx, (float)buttons[i].config->current / buttons[i].config->max, start + i * (height + separation) + height * 0.5, rgb(255, 255, 255));
		}
		i++;
	}
	if (i == focus)
		put_centered_scaled_image(ctx, &buttons[i].focus_image, height, start + i * (height + separation));
	else
		put_centered_scaled_image(ctx, &buttons[i].image, height, start + i * (height + separation));
}

void	open_config(t_context *ctx)
{
	int	buttons_start;

	ctx->mode = CONFIG;
	if (ctx->render)
	{
		fill_screen(ctx, rgb(0,10,20));
		buttons_start = put_centered_scaled_image(ctx, &ctx->textures.title, ctx->height * 0.3, ctx->height * 0.07) + ctx->height * 0.13;
		mlx_put_image_to_window(ctx->mlx, ctx->window, ctx->screen.img, 0, 0);
		put_buttons(ctx, ctx->config_buttons, C_SIZE, ctx->config_focus, buttons_start);
	}
}
