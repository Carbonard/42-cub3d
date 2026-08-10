/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_mouse_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 16:17:38 by elangari          #+#    #+#             */
/*   Updated: 2026/08/09 16:49:24 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	check_mouse(t_context *ctx)
{
	int	x;
	int	y;
	int	game_x;

	mlx_mouse_get_pos(ctx->mlx, ctx->window, &x, &y);
	if (y < 20)
		return (0);
	game_x = x - (ctx->screen.width / 2);
	if (!game_x)
		return (0);
	mlx_mouse_move(ctx->mlx, ctx->window,
		ctx->screen.width / 2, ctx->screen.height / 2);
	mlx_mouse_get_pos(ctx->mlx, ctx->window, &x, &y);
	rotate_player(ctx, (double)(game_x * ctx->player.mouse_sensitivity));
	return (1);
}
