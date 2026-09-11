/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_render_screen.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 17:07:26 by rselva-2          #+#    #+#             */
/*   Updated: 2026/09/11 21:10:09 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

t_mlx_image	*last_step(t_context *ctx,
				t_ray *ray, t_vector *dist_to, char last_cross)
{
	t_mlx_image	*texture;

	if (last_cross == 'x')
	{
		ray->dist = dist_to->x - ray->dir_inv.x;
		if (ray->dir.x > 0)
			texture = &ctx->textures.east;
		else
			texture = &ctx->textures.west;
	}
	else
	{
		ray->dist = dist_to->y - ray->dir_inv.y;
		if (ray->dir.y > 0)
			texture = &ctx->textures.south;
		else
			texture = &ctx->textures.north;
	}
	// if (ray->dist < 0.0001)
	// 	ray->dist = 0.0001;
	ray->pos.x = ctx->player.pos.x + ray->dir.x * ray->dist;
	ray->pos.y = ctx->player.pos.y + ray->dir.y * ray->dist;
	return (texture);
}

static void	trace_ray_3(t_vector *dist_to, t_ray *ray, t_vector *map_cell, char *last_cross)
{
	if (dist_to->x < dist_to->y)
	{
		map_cell->x += ray->dir_sgn.x;
		dist_to->x += ray->dir_inv.x;
		*last_cross = 'x';
	}
	else
	{
		map_cell->y += ray->dir_sgn.y;
		dist_to->y += ray->dir_inv.y;
		*last_cross = 'y';
	}
}

static void	trace_ray_2(t_context *ctx, t_ray *ray, t_int_vector *screen)
{
	t_vector		dist_to;
	t_vector		map_cell;
	char			last_cross;

	dist_to.x = ray->h_dist(ctx->player.pos.x) * ray->dir_inv.x;
	dist_to.y = ray->v_dist(ctx->player.pos.y) * ray->dir_inv.y;
	map_cell.x = ctx->player.pos.x;
	map_cell.y = ctx->player.pos.y;
	last_cross = 0;
	while (!is_wall(&ctx->map, &map_cell))
		trace_ray_3(&dist_to, ray, &map_cell, &last_cross);
	display_vertical_slice(ctx, screen, ray,
		last_step(ctx, ray, &dist_to, last_cross));
}

static void	trace_ray(t_context *ctx, t_int_vector *screen)
{
	t_ray	ray;
	double	scale_screen_factor;

	scale_screen_factor = (double)(screen->x * 2) / ctx->width - 1;
	ray.dir.x = ctx->player.dir.x + scale_screen_factor * ctx->player.ort.x;
	ray.dir.y = ctx->player.dir.y + scale_screen_factor * ctx->player.ort.y;
	ray.pos.x = ctx->player.pos.x;
	ray.pos.y = ctx->player.pos.y;
	if (ray.dir.x > 0)
		ray.h_dist = upper_dist;
	else
		ray.h_dist = lower_dist;
	if (ray.dir.y > 0)
		ray.v_dist = upper_dist;
	else
		ray.v_dist = lower_dist;
	// test division by 0 in clusters
	ray.dir_inv.x = 1 / fabs(ray.dir.x);
	ray.dir_inv.y = 1 / fabs(ray.dir.y);
	ray.dir_sgn.x = (ray.dir.x > 0) - (ray.dir.x < 0);
	ray.dir_sgn.y = (ray.dir.y > 0) - (ray.dir.y < 0);
	trace_ray_2(ctx, &ray, screen);
}

void	render_screen(t_context *ctx)
{
	t_int_vector	screen_coord;

	screen_coord.x = 0;
	while (screen_coord.x < ctx->width)
	{
		screen_coord.y = 0;
		trace_ray(ctx, &screen_coord);
		screen_coord.x++;
	}
	render_minimap(ctx);
}
