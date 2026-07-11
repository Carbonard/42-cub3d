/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_mouse_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elangari <elangari@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 16:17:38 by elangari          #+#    #+#             */
/*   Updated: 2026/07/11 20:23:40 by elangari         ###   ########.fr       */
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
	rotate_player(ctx, (double)(game_x * 0.125) * ctx->player.ang_velocity);
	return (1);
}