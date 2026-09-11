/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_menu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 15:39:09 by rselva-2          #+#    #+#             */
/*   Updated: 2026/09/11 22:51:16 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	fill_screen(t_context *ctx, t_color color)
{
	int	i;
	int	j;

	i = 0;
	while (i < ctx->width)
	{
		j = 0;
		while (j < ctx->height)
		{
			put_pixel(&ctx->screen, i, j, color);
			j++;
		}
		i++;
	}
}

int	put_centered_scaled_image(t_context *ctx, t_mlx_image *image,
		int height, int y0)
{
	double	factor;
	int		x0;
	int		x;
	int		y;

	factor = (double)image->height / height;
	x0 = ctx->width / 2 - image->width / factor / 2;
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

static void	put_buttons(t_context *ctx, t_menu_button *buttons, int start)
{
	int	i;
	int	height;
	int	sep;

	sep = 20;
	height = fmin((ctx->height - start) / B_SIZE - sep, ctx->height * 0.1);
	i = 0;
	while (i < B_SIZE)
	{
		if (i == ctx->focus)
			put_centered_scaled_image(ctx, &buttons[i].focus_image,
				height, start + i * (height + sep));
		else
			put_centered_scaled_image(ctx, &buttons[i].image,
				height, start + i * (height + sep));
		i++;
	}
}

void	open_menu(t_context *ctx)
{
	int	buttons_start;

	ctx->mode = MENU;
	if (ctx->render)
	{
		fill_screen(ctx, rgb(0, 10, 20));
		buttons_start = put_centered_scaled_image(ctx, &ctx->textures.title,
				ctx->height * 0.3, ctx->height * 0.07) + ctx->height * 0.13;
		put_buttons(ctx, ctx->buttons, buttons_start);
		resize_screen(ctx);
		mlx_put_image_to_window(ctx->mlx, ctx->window,
			ctx->real_screen.img, 0, 0);
	}
}
