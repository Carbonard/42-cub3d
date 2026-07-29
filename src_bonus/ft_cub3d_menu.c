/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_menu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 15:39:09 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/28 01:59:12 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	fill_screen(t_context *ctx, unsigned int color)
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

int	put_centered_scaled_image(t_context *ctx, t_mlx_image *image, int height, int y0)
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

static void	put_buttons(t_context *ctx, t_menu_button *buttons, int size, int focus, int start)
{
	int	i;
	int	height;
	int	separation;

	separation = 20;
	height = fmin((ctx->height - start) / size - separation, ctx->height * 0.1);
	i = 0;
	while (i < size)
	{
		if (i == focus)
			put_centered_scaled_image(ctx, &buttons[i].focus_image, height, start + i * (height + separation));
		else
			put_centered_scaled_image(ctx, &buttons[i].image, height, start + i * (height + separation));
		i++;
	}
}

void	open_menu(t_context *ctx)
{
	int	buttons_start;

	ctx->mode = MENU;
	if (ctx->render)
	{
		fill_screen(ctx, rgb(0,10,20));
		buttons_start = put_centered_scaled_image(ctx, &ctx->textures.title, ctx->height * 0.3, ctx->height * 0.07) + ctx->height * 0.13;
		mlx_put_image_to_window(ctx->mlx, ctx->window, ctx->screen.img, 0, 0);
		put_buttons(ctx, ctx->buttons, B_SIZE, ctx->focus, buttons_start);
	}
}
