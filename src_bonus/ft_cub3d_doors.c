/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_doors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 17:33:54 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/10 21:02:53 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

char	*colision_map_point(t_context *ctx, t_int_vector *coord, t_int_vector *step, t_vector *delta)
{
	t_vector		dist;

	if (ctx->player.dir.x > 0)
		dist.x = upper_dist(ctx->player.pos.x) * delta->x;
	else
		dist.x = lower_dist(ctx->player.pos.x) * delta->x;
	if (ctx->player.dir.y > 0)
		dist.y = upper_dist(ctx->player.pos.y) * delta->y;
	else
		dist.y = lower_dist(ctx->player.pos.y) * delta->y;
	while (ctx->map.matrix[coord->y][coord->x] == FLOOR
		|| (coord->x == (int)ctx->player.pos.x && coord->y == (int)ctx->player.pos.y))
	{
		if (dist.x < dist.y)
		{
			dist.x += delta->x;
			coord->x += step->x;
		}
		else
		{
			dist.y += delta->y;
			coord->y += step->y;
		}
	}
	return (&ctx->map.matrix[coord->y][coord->x]);
}

void	open_door(t_context *ctx)
{
	t_int_vector	coord;
	t_int_vector	step;
	t_vector		delta;
	char			*colision_point;

	coord.x = ctx->player.pos.x;
	coord.y = ctx->player.pos.y;
	step.x = (ctx->player.dir.x > 0) - (ctx->player.dir.x < 0);
	step.y = (ctx->player.dir.y > 0) - (ctx->player.dir.y < 0);
	delta.x = 1 / fabs(ctx->player.dir.x);
	delta.y = 1 / fabs(ctx->player.dir.y);
	colision_point = colision_map_point(ctx, &coord, &step, &delta);
	if (*colision_point == OPEN_DOOR || *colision_point == CLOSED_DOOR)
		*colision_point ^= CLOSED_DOOR ^ OPEN_DOOR;
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
