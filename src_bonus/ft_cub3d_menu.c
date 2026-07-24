/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_menu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 15:39:09 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/20 17:11:34 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	put_square(t_context *ctx, t_int_vector *position, t_int_vector *size, unsigned int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size->x)
	{
		j = 0;
		while (j < size->y)
		{
			put_pixel(
				&ctx->screen,
				position->x + i,
				position->y + j,
				color);
			j++;
		}
		i++;
	}
}

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

int	put_title(t_context *ctx, t_mlx_image *title)
{
	int			i;
	int			j;
	t_vector	resize;
	t_vector	screen_pos;
	t_vector	size;

	size.x = ctx->height * 0.6;
	size.y = ctx->height * 0.3;
	screen_pos.x = ctx->width * 0.05;
	screen_pos.y = ctx->height * 0.05;
	resize.x = (double)title->width / size.x;
	resize.y = (double)title->height / size.y;
	j = 0;
	while (j < size.y)
	{
		i = 0;
		while (i < size.x)
		{
			put_pixel(&ctx->screen,
				screen_pos.x + i, screen_pos.y + j,
				merge_colors(
					get_pixel(&ctx->screen,
						screen_pos.x + i, screen_pos.y + j),
					get_pixel(title, resize.x * i, resize.y * j)));
			i++;
		}
		j++;
	}
	return (screen_pos.y + j);
}

void	open_menu(t_context *ctx)
{
	int	i;
	int	buttons_start;

	if (ctx->render)
	{
		fill_screen(ctx, rgb(0,20,50));
		buttons_start = put_title(ctx, &ctx->textures.title) + 50;
		mlx_put_image_to_window(ctx->mlx, ctx->window, ctx->screen.img, 0, 0);
		i = 0;
		while (i < B_SIZE)
		{
			if (ctx->focus == i)
				mlx_put_image_to_window(ctx->mlx, ctx->window, ctx->buttons[i].focus_image.img, 100, buttons_start + i * 150);
			else
				mlx_put_image_to_window(ctx->mlx, ctx->window, ctx->buttons[i].image.img, 100, buttons_start + i * 150);
			i++;
		}
	}
}
