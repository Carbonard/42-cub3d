/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_raycasting.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 03:25:45 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/11 17:59:51 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	init_ray_casting(t_context *ctx, t_ray_cast *rc, t_vector *dir)
{
	rc->map_cell.x = ctx->player.pos.x;
	rc->map_cell.y = ctx->player.pos.y;
	rc->step.x = (dir->x > 0) - (dir->x < 0);
	rc->step.y = (dir->y > 0) - (dir->y < 0);
	rc->delta.x = 1 / fabs(dir->x);
	rc->delta.y = 1 / fabs(dir->y);
	if (dir->x > 0)
		rc->next_cell.x = (ceil(ctx->player.pos.x) - ctx->player.pos.x) * rc->delta.x;
	else
		rc->next_cell.x = (ctx->player.pos.x - floor(ctx->player.pos.x)) * rc->delta.x;
	if (dir->y > 0)
		rc->next_cell.y = (ceil(ctx->player.pos.y) - ctx->player.pos.y) * rc->delta.y;
	else
		rc->next_cell.y = (ctx->player.pos.y - floor(ctx->player.pos.y)) * rc->delta.y;
}

// void	ray_casting(t_context *ctx, t_vector *dir, t_ray_cast *rc)
// {
// 	init_ray_casting(ctx, dir);
// 	while (ctx->map.matrix[rc->map_cell.y][rc->map_cell.x] == FLOOR)
// 	{
// 		if (rc->next_cell.x < rc->next_cell.y)
// 		{
// 			rc->final_dist = rc->next_cell.x;
// 			rc->next_cell.x += rc->delta.x;
// 			rc->map_cell.x += rc->step.x;
// 		}
// 		else
// 		{
// 			rc->final_dist = rc->next_cell.y;
// 			rc->next_cell.y += rc->delta.y;
// 			rc->map_cell.y += rc->step.y;
// 		}
// 	}
// }
