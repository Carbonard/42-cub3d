/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_render_screen.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 17:07:26 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/09 00:18:27 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

// t_mlx_image	*last_step(t_context *ctx,
// 				double last_step, t_ray *ray, t_vector *last_jump)
// {
// 	if (last_step < ray->h_dist(ray->pos.x) / fabs(ray->dir.x))
// 		last_step = ray->v_dist(ray->pos.y) / fabs(ray->dir.y);
// 	else
// 		last_step = ray->h_dist(ray->pos.x) / fabs(ray->dir.x);
// 	last_jump->x = ray->pos.x;
// 	ray->pos.y += last_step * ray->dir.y;
// 	ray->pos.x += last_step * ray->dir.x;
// 	if (!is_wall(&ctx->map, last_jump))
// 	{
// 		if (ray->dir.x > 0)
// 			return (&ctx->textures.east);
// 		else
// 			return (&ctx->textures.west);
// 	}
// 	else
// 	{
// 		if (ray->dir.y > 0)
// 			return (&ctx->textures.south);
// 		else
// 			return (&ctx->textures.north);
// 	}
// }

// static void	trace_ray_2(t_context *ctx, t_ray *ray, t_int_vector *screen)
// {
// 	double			step;
// 	t_mlx_image		*texture;
// 	t_vector		tmp;

// 	texture = NULL;
// 	while (!is_wall(&ctx->map, &ray->pos))
// 	{
// 		step = get_step_size(ray);
// 		// printf("step: %lf\n", step);
// 		tmp.x = ray->pos.x + ray->dir.x * step;
// 		tmp.y = ray->pos.y + ray->dir.y * step;
// 		if (is_wall(&ctx->map, &tmp))
// 		{
// 			texture = last_step(ctx, step, ray, &tmp);
// 			break ;
// 		}
// 		ray->pos.x = tmp.x;
// 		ray->pos.y = tmp.y;
// 	}
// 	if (!on_map(&ctx->map, &ray->pos))
// 		texture = NULL;
// 	display_vertical_slice(ctx, screen, ray, texture);
// }

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
	if (ray->dist < 0.0001)
		ray->dist = 0.0001;
	ray->pos.x = ctx->player.pos.x + ray->dir.x * ray->dist;
	ray->pos.y = ctx->player.pos.y + ray->dir.y * ray->dist;
	return (texture);
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
	while (!is_wall(&ctx->map, &map_cell))
	{
		if (dist_to.x < dist_to.y)
		{
			map_cell.x += ray->dir_sgn.x;
			dist_to.x += ray->dir_inv.x;
			last_cross = 'x';
		}
		else
		{
			map_cell.y += ray->dir_sgn.y;
			dist_to.y += ray->dir_inv.y;
			last_cross = 'y';
		}
	}
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
	// normalize_vector(&ray.dir);
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

// size_t t = get_time();
// static size_t total_time;
// static size_t cnt;

// cnt++;
// total_time += get_time() - t;
// if (cnt == 1000){
//printf("mean time int %lu iterations: %lf\n", cnt, (double)total_time / cnt);
// cnt = 0;
// total_time = 0;}