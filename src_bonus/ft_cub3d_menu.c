/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_menu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 15:39:09 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/16 18:03:50 by rselva-2         ###   ########.fr       */
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

void	open_menu(t_context *ctx)
{
	int	i;

	fill_screen(ctx, rgb(50,50,50));
	mlx_put_image_to_window(ctx->mlx, ctx->window, ctx->screen.img, 0, 0);
	i = 0;
	while (i < B_SIZE)
	{
		if (ctx->focus == i)
			mlx_put_image_to_window(ctx->mlx, ctx->window, ctx->buttons[i].focus_image.img, 100, 100 + i * 150);
		else
			mlx_put_image_to_window(ctx->mlx, ctx->window, ctx->buttons[i].image.img, 100, 100 + i * 150);
		i++;
	}
}
