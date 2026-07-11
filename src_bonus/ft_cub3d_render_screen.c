/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_render_screen.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 17:07:26 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/11 17:39:57 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void time(int step)
{
	static size_t t = 0;
	static size_t total_time = 0;
	static size_t cnt = 0;
	static int first_time = 1;

	if (step == 1)
	{
		t = get_time();
	}
	else
	{
		cnt++;
		total_time += get_time() - t;
		if (cnt % 100 == 0)
		{
			printf("time mean after %lu iterations: %lf\n", cnt, (double)total_time / cnt);
			if (first_time)
			{
				cnt = 0;
				total_time = 0;
				first_time = 0;
			}
		}
	}
}

t_texture	*get_texture(t_context *ctx, t_ray_info *ray, t_vector *dir)
{
	if (ray->tex.type == WALL)
	{
		if (ray->tex.orientation == AXIS_X && dir->x > 0)
			return (ctx->textures.east.current);
		else if (ray->tex.orientation == AXIS_X)
			return (ctx->textures.west.current);
		else if (dir->y > 0)
			return (ctx->textures.south.current);
		else
			return (ctx->textures.north.current);
	}
	else if (ray->tex.type == CLOSED_DOOR)
	{
		return (ctx->textures.door.current);
		if (ray->tex.orientation == AXIS_X && dir->x > 0)
			return (ctx->textures.east.current);
		else if (ray->tex.orientation == AXIS_X)
			return (ctx->textures.west.current);
		else if (dir->y > 0)
			return (ctx->textures.south.current);
		else
			return (ctx->textures.north.current);
	}
	return (NULL);
}

static void	trace_ray(t_context *ctx, t_ray_info *ray, t_vector *direction)
{
	t_ray_cast	rc;

	init_ray_casting(ctx, &rc, direction);
	while (ctx->map.matrix[rc.map_cell.y][rc.map_cell.x] != WALL
		&& ctx->map.matrix[rc.map_cell.y][rc.map_cell.x] != CLOSED_DOOR)
	{
		if (rc.next_cell.x < rc.next_cell.y)
		{
			ray->dist = rc.next_cell.x;
			rc.map_cell.x += rc.step.x;
			rc.next_cell.x += rc.delta.x;
			ray->tex.orientation = AXIS_X;
		}
		else
		{
			ray->dist = rc.next_cell.y;
			rc.map_cell.y += rc.step.y;
			rc.next_cell.y += rc.delta.y;
			ray->tex.orientation = AXIS_Y;
		}
	}
	ray->tex.type = ctx->map.matrix[rc.map_cell.y][rc.map_cell.x];
	ray->pos.x = ctx->player.pos.x + direction->x * ray->dist;
	ray->pos.y = ctx->player.pos.y + direction->y * ray->dist;
	save_walls(ctx, ray, get_texture(ctx, ray, direction));
}

void	render_screen(t_context *ctx)
{
	t_ray_info	ray;
	t_vector	direction;
	double	scale_screen_factor;

time(1);
	ray.screen_x = 0;
	while (ray.screen_x < ctx->width)
	{
		scale_screen_factor = (double)(ray.screen_x * 2) / ctx->width - 1;
		direction.x = ctx->player.dir.x
			+ scale_screen_factor * ctx->player.ort.x;
		direction.y = ctx->player.dir.y
			+ scale_screen_factor * ctx->player.ort.y;
		trace_ray(ctx, &ray, &direction);
		ray.screen_x++;
	}
	fill_screen(ctx);
time(2);
	render_minimap(ctx);
}
