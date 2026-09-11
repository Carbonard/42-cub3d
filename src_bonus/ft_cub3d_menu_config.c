/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_menu_config.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/28 01:58:21 by rselva-2          #+#    #+#             */
/*   Updated: 2026/09/10 19:23:48 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

static int	put_left_aligned_scaled_image(t_context *ctx, t_mlx_image *image,
				int height, int y0)
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

void	put_circle(t_mlx_image *image, int x, int y, t_color color)
{
	int	i;
	int	j;
	int	rad;

	rad = 6;
	i = -rad;
	while (i <= rad)
	{
		j = -rad;
		while (j <= rad)
		{
			if (i * i + j * j < rad * rad)
				put_pixel(image, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	bar_min_max(t_context *ctx, float percent, int y0, int focus)
{
	int				i;
	int				start;
	int				end;
	int				y;
	unsigned int	color;

	if (focus)
		color = rgb(128, 128, 221);
	else
		color = rgb(250, 250, 250);
	start = ctx->width * 0.6;
	end = ctx->width * 0.9;
	y = y0 - 1;
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
		percent * (end - start) + start, y0, color);
}

static void	put_buttons(t_context *ctx, t_config_button *buttons, int start)
{
	int				i;
	int				height;
	int				sep;

	sep = 20;
	height = fmin((ctx->height - start) / C_SIZE - sep, ctx->height * 0.1);
	i = 0;
	while (i < C_SIZE - 1)
	{
		put_left_aligned_scaled_image(ctx,
			&buttons[i].image[i == ctx->config_focus],
			height,
			start + i * (height + sep));
		bar_min_max(ctx,
			(float)buttons[i].config->current / buttons[i].config->max,
			start + i * (height + sep) + height * 0.5,
			i == ctx->config_focus);
		i++;
	}
	put_centered_scaled_image(ctx, &buttons[i].image[i == ctx->config_focus],
		height,
		start + i * (height + sep));
}

void	open_config(t_context *ctx)
{
	int	buttons_start;

	ctx->mode = CONFIG;
	if (ctx->render)
	{
		fill_screen(ctx, rgb(0, 10, 20));
		buttons_start = put_centered_scaled_image(ctx, &ctx->textures.title,
				ctx->height * 0.3, ctx->height * 0.07) + ctx->height * 0.13;
		put_buttons(ctx, ctx->config_buttons, buttons_start);
		resize_screen(ctx);
		mlx_put_image_to_window(ctx->mlx, ctx->window, ctx->real_screen.img, 0, 0);
	}
}
