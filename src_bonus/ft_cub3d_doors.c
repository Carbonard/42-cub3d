/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_doors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 17:33:54 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/15 22:08:42 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	open_door(t_context *ctx)
{
	t_ray_cast	rc;
	char		*colision_point;

	init_ray_casting(ctx, &rc, &ctx->player.dir);
	while (ctx->map.matrix[rc.map_cell.y][rc.map_cell.x] == FLOOR
		|| ctx->map.matrix[rc.map_cell.y][rc.map_cell.x] == EXPLOSION
		|| (rc.map_cell.x == (int)ctx->player.pos.x
			&& rc.map_cell.y == (int)ctx->player.pos.y))
	{
		if (rc.next_cell.x < rc.next_cell.y)
		{
			rc.next_cell.x += rc.delta.x;
			rc.map_cell.x += rc.step.x;
		}
		else
		{
			rc.next_cell.y += rc.delta.y;
			rc.map_cell.y += rc.step.y;
		}
	}
	colision_point = &ctx->map.matrix[rc.map_cell.y][rc.map_cell.x];
	if (*colision_point == OPEN_DOOR || *colision_point == CLOSED_DOOR)
		*colision_point ^= CLOSED_DOOR ^ OPEN_DOOR;
	if (*colision_point == ENEMY)
		*colision_point = EXPLOSION;
}

// void	open_door(t_context *ctx)
// {
// 	int	x;
// 	int	y;
// 	int	d_x;
// 	int	d_y;

// 	x = ctx->player.pos.x;
// 	y = ctx->player.pos.y;
// 	d_x = (ctx->player.dir.x > 0) - (ctx->player.dir.x < 0);
// 	d_y = (ctx->player.dir.y > 0) - (ctx->player.dir.y < 0);
// 	if (fabs(ctx->player.dir.x) > fabs(ctx->player.dir.y))
// 	{
// 		if (ctx->map.matrix[y][x + d_x] == 'D' || ctx->map.matrix[y][x + d_x] == 'd')
// 			ctx->map.matrix[y][x + d_x] ^= 'd'^'D';
// 		else if (ctx->map.matrix[y + d_y][x + d_x] == 'D' || ctx->map.matrix[y + d_y][x + d_x] == 'd')
// 				ctx->map.matrix[y + d_y][x + d_x] ^= 'd'^'D';
// 		else if (ctx->map.matrix[y][x + 2 * d_x] == 'D' || ctx->map.matrix[y][x + 2 * d_x] == 'd')
// 				ctx->map.matrix[y][x + 2 * d_x] ^= 'd'^'D';
// 		else if (ctx->map.matrix[y + d_y][x] == 'D' || ctx->map.matrix[y + d_y][x] == 'd')
// 				ctx->map.matrix[y + d_y][x] ^= 'd'^'D';
// 	}
// 	else
// 	{
// 		if (ctx->map.matrix[y + d_y][x] == 'D' || ctx->map.matrix[y + d_y][x] == 'd')
// 			ctx->map.matrix[y + d_y][x] ^= 'd'^'D';
// 		else if (ctx->map.matrix[y + d_y][x + d_x] == 'D' || ctx->map.matrix[y + d_y][x + d_x] == 'd')
// 			ctx->map.matrix[y + d_y][x + d_x] ^= 'd'^'D';
// 		else if (ctx->map.matrix[y + 2 * d_y][x] == 'D' || ctx->map.matrix[y + 2 * d_y][x] == 'd')
// 			ctx->map.matrix[y + 2 * d_y][x] ^= 'd'^'D';
// 		else if (ctx->map.matrix[y + d_y][x] == 'D' || ctx->map.matrix[y + d_y][x] == 'd')
// 			ctx->map.matrix[y + d_y][x] ^= 'd'^'D';
// 	}
// }
