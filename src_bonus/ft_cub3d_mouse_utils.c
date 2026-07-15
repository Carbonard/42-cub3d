/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_mouse_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 16:17:38 by elangari          #+#    #+#             */
/*   Updated: 2026/07/15 19:14:06 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	check_mouse(t_context *ctx)
{
	int	x = 0;
	int	y = 0;
	int	game_x;
	
	mlx_mouse_get_pos(ctx->mlx, ctx->window, &x, &y);
	game_x = x - (ctx->screen.width / 2);
	if (!game_x)
		return (0);
	mlx_mouse_move(ctx->mlx, ctx->window, ctx->screen.width / 2, ctx->screen.height / 2);
	mlx_mouse_get_pos(ctx->mlx, ctx->window, &x, &y);
	// printf("mouse: %i, %i\n", x, y);
	rotate_player(ctx, (double)(game_x * ctx->player.mouse_sensitivity));
	return (1);
}