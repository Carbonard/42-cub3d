/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_render_screen_raycasting.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 15:05:11 by rselva-2          #+#    #+#             */
/*   Updated: 2026/08/10 15:36:12 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

static t_explosion	*save_explosion(t_context *ctx, t_int_vector *cell)
{
	int	i;

	i = 0;
	while (i < ctx->n_explosions)
	{
		if (ctx->explosions[i].map.x == cell->x
			&& ctx->explosions[i].map.y == cell->y)
			return (&ctx->explosions[i]);
		i++;
	}
	ctx->explosions[ctx->n_explosions].map.x = cell->x;
	ctx->explosions[ctx->n_explosions].map.y = cell->y;
	ctx->explosions[ctx->n_explosions].time = get_time();
	ctx->n_explosions++;
	return (&ctx->explosions[ctx->n_explosions - 1]);
}

static void	save_enemy(t_context *ctx, t_int_vector *cell)
{
	int	i;

	i = 0;
	while (i < ctx->n_enemies)
	{
		if ((int)ctx->enemies[i].map.x == cell->x
			&& (int)ctx->enemies[i].map.y == cell->y)
			return ;
		i++;
	}
	ctx->enemies[ctx->n_enemies].map.x = cell->x + 0.5;
	ctx->enemies[ctx->n_enemies].map.y = cell->y + 0.5;
	ctx->enemies[ctx->n_enemies].type = ctx->map.matrix[cell->y][cell->x];
	if (ctx->enemies[ctx->n_enemies].type == EXPLOSION)
		ctx->enemies[ctx->n_enemies].explosion = save_explosion(ctx, cell);
	ctx->n_enemies++;
}

static void	step(t_ray_info *ray, t_ray_cast *rc)
{
	if (rc->next_cell.x < rc->next_cell.y)
	{
		ray->dist = rc->next_cell.x;
		rc->map_cell.x += rc->step.x;
		rc->next_cell.x += rc->delta.x;
		ray->tex.orientation = AXIS_X;
	}
	else
	{
		ray->dist = rc->next_cell.y;
		rc->map_cell.y += rc->step.y;
		rc->next_cell.y += rc->delta.y;
		ray->tex.orientation = AXIS_Y;
	}
}

void	trace_ray(t_context *ctx, t_ray_info *ray, t_vector *direction)
{
	t_ray_cast	rc;

	init_ray_casting(ctx, &rc, direction);
	while (ctx->map.matrix[rc.map_cell.y][rc.map_cell.x] != WALL
		&& ctx->map.matrix[rc.map_cell.y][rc.map_cell.x] != CLOSED_DOOR
		&& ctx->map.matrix[rc.map_cell.y][rc.map_cell.x] != EXIT)
	{
		step(ray, &rc);
		if (ctx->map.matrix[rc.map_cell.y][rc.map_cell.x] == ENEMY
			|| ctx->map.matrix[rc.map_cell.y][rc.map_cell.x] == EXPLOSION)
			save_enemy(ctx, &rc.map_cell);
	}
	ray->tex.type = ctx->map.matrix[rc.map_cell.y][rc.map_cell.x];
	ray->pos.x = ctx->player.pos.x + direction->x * ray->dist;
	ray->pos.y = ctx->player.pos.y + direction->y * ray->dist;
}
