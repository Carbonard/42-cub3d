/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_mouse_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 16:17:38 by elangari          #+#    #+#             */
/*   Updated: 2026/09/11 23:07:42 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	activate_mouse(t_context *ctx, int activate)
{
	int	x;
	int	y;

	ctx->mouse_active = !!activate;
	if (ENABLE_MOUSE_HIDE)
	{
		if (activate)
			mlx_mouse_hide(ctx->mlx, ctx->window);
		else
			mlx_mouse_show(ctx->mlx, ctx->window);
	}
	mlx_mouse_move(ctx->mlx, ctx->window,
		ctx->screen.width / 2, ctx->screen.height / 2);
	mlx_mouse_get_pos(ctx->mlx, ctx->window, &x, &y);
}

int	check_mouse(t_context *ctx)
{
	int	x;
	int	y;
	int	width_center;
	int	height_center;
	int	game_x;

	if (!ctx->mouse_active)
		return (0);
	width_center = ctx->width * ctx->pix_size / 2;
	height_center = ctx->height * ctx->pix_size / 2;
	mlx_mouse_get_pos(ctx->mlx, ctx->window, &x, &y);
	if (y < 20)
		return (0);
	game_x = x - width_center;
	if (!game_x)
		return (0);
	mlx_mouse_move(ctx->mlx, ctx->window, width_center, height_center);
	mlx_mouse_get_pos(ctx->mlx, ctx->window, &x, &y);
	rotate_player(ctx, (double)(game_x * ctx->player.mouse_sensitivity));
	return (1);
}
