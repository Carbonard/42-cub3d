/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_shoot.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 17:33:54 by rselva-2          #+#    #+#             */
/*   Updated: 2026/09/04 17:27:58 by rselva-2         ###   ########.fr       */
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

void	manage_collision(t_context *ctx, char *collision_point)
{
	if (*collision_point == OPEN_DOOR || *collision_point == CLOSED_DOOR)
	{
		*collision_point ^= CLOSED_DOOR ^ OPEN_DOOR;
		initialize_minimap(ctx);
	}
	if (*collision_point == ENEMY)
		*collision_point = EXPLOSION * (!!ctx->textures.explosion.size)
			+ FLOOR * (!ctx->textures.explosion.size);
}

void	shoot(t_context *ctx)
{
	t_ray_cast	rc;

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
	manage_collision(ctx, &ctx->map.matrix[rc.map_cell.y][rc.map_cell.x]);
}
