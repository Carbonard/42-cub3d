/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_shoot.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 17:33:54 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/24 14:41:23 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	shooting_ray_must_continue(t_context *ctx, t_ray_cast *rc)
{
	if (ctx->map.matrix[rc->map_cell.y][rc->map_cell.x] == FLOOR)
		return (1);
	if (ctx->map.matrix[rc->map_cell.y][rc->map_cell.x] == EXPLOSION)
		return (1);
	if (rc->map_cell.x == (int)ctx->player.pos.x
			&& rc->map_cell.y == (int)ctx->player.pos.y)
		return (1);
	return (0);
}

void	shoot(t_context *ctx)
{
	t_ray_cast	rc;
	char		*colision_point;

	init_ray_casting(ctx, &rc, &ctx->player.dir);
	while (shooting_ray_must_continue(ctx, &rc))
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
		*colision_point = EXPLOSION * (!!ctx->textures.explosion.size)
			+ FLOOR * (!ctx->textures.explosion.size);
}
