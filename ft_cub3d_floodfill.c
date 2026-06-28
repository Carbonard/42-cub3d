/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_floodfill.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elangari <elangari@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 18:54:24 by elangari          #+#    #+#             */
/*   Updated: 2026/06/28 19:11:52 by elangari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	flood_fill(t_context *ctx, int x, int y)
{
	if (x < 0 || x > ctx->map.width
	|| y < 0 || y > ctx->map.height)
		return (1);
	if (ctx->map.matrix[y][x] == 1)
		return (0);
	if (flood_fill(ctx, x + 1, y))
		return (1);
	if (flood_fill(ctx, x - 1, y))
		return (1);
	if (flood_fill(ctx, x, y + 1))
		return (1);
	if (flood_fill(ctx, x, y - 1))
		return (1);
	return (0);
}