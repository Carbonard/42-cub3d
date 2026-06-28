/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_close.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 13:59:21 by rselva-2          #+#    #+#             */
/*   Updated: 2026/06/28 14:05:18 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	close_images(t_context *ctx)
{
	if (ctx->map.img.img)
	{
		mlx_destroy_image(ctx->mlx, ctx->map.img.img);
		ctx->map.img.img = NULL;
	}
	if (ctx->player.minimap_img.img)
	{
		mlx_destroy_image(ctx->mlx, ctx->player.minimap_img.img);
		ctx->player.minimap_img.img = NULL;
	}
}

int	close_window(void *arg)
{
	t_context	*ctx;

	ctx = arg;
	close_images(ctx);
	mlx_destroy_window(ctx->mlx, ctx->window);
	mlx_destroy_display(ctx->mlx);
	free(ctx->mlx);
	exit (0);
	return (0);
}
