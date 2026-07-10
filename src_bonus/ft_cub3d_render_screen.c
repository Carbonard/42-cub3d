/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_render_screen.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 17:07:26 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/10 17:36:06 by rselva-2         ###   ########.fr       */
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

t_texture	*get_texture(t_context *ctx, t_tex_info *info, t_ray_info *ray)
{
	if (info->type == WALL)
	{
		if (info->orientation == AXIS_X && ray->dir.x > 0)
			return (ctx->textures.east.current);
		else if (info->orientation == AXIS_X)
			return (ctx->textures.west.current);
		else if (ray->dir.y > 0)
			return (ctx->textures.south.current);
		else
			return (ctx->textures.north.current);
	}
	else if (info->type == CLOSED_DOOR)
	{
		return (ctx->textures.door.current);
		if (info->orientation == AXIS_X && ray->dir.x > 0)
			return (ctx->textures.east.current);
		else if (info->orientation == AXIS_X)
			return (ctx->textures.west.current);
		else if (ray->dir.y > 0)
			return (ctx->textures.south.current);
		else
			return (ctx->textures.north.current);
	}
	// printf("type: %c\n", info->type);
	return (NULL);
}

t_texture	*last_step(t_context *ctx,
				t_ray_info *ray, t_vector *dist_to)
{
	t_texture	*texture;

	if (ray->tex.orientation == AXIS_X || ray->dir.y == 0)
		ray->dist = dist_to->x - ray->dir_inv.x;
	else
		ray->dist = dist_to->y - ray->dir_inv.y;
	if (ray->dist < 0.001)
		ray->dist = 0.001;
	ray->pos.x = ctx->player.pos.x + ray->dir.x * ray->dist;
	ray->pos.y = ctx->player.pos.y + ray->dir.y * ray->dist;
	texture = get_texture(ctx, &ray->tex, ray);
	return (texture);
}

static void	trace_ray_2(t_context *ctx, t_ray_info *ray)
{
	t_vector	dist_to;
	t_vector	map_cell;

	dist_to.x = ray->h_dist(ctx->player.pos.x) * ray->dir_inv.x;
	dist_to.y = ray->v_dist(ctx->player.pos.y) * ray->dir_inv.y;
	map_cell.x = ctx->player.pos.x;
	map_cell.y = ctx->player.pos.y;
	while (is_floor(&ctx->map, &map_cell))
	{
		if (dist_to.x < dist_to.y)
		{
			map_cell.x += ray->dir_sgn.x;
			dist_to.x += ray->dir_inv.x;
			ray->tex.orientation = AXIS_X;
		}
		else
		{
			map_cell.y += ray->dir_sgn.y;
			dist_to.y += ray->dir_inv.y;
			ray->tex.orientation = AXIS_Y;
		}
	}
	ray->tex.type = ctx->map.matrix[(int)map_cell.y][(int)map_cell.x];
	save_walls(ctx, ray, last_step(ctx, ray, &dist_to));
}

static void	trace_ray(t_context *ctx, int screen_x)
{
	t_ray_info	ray;
	double	scale_screen_factor;

	scale_screen_factor = (double)(screen_x * 2) / ctx->width - 1;
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
	ray.screen_x = screen_x;
	trace_ray_2(ctx, &ray);
}

void	render_screen(t_context *ctx)
{
	int	screen_x;

	set_textures(ctx);
time(1);
	screen_x = 0;
	while (screen_x < ctx->width)
	{
		trace_ray(ctx, screen_x);
		screen_x++;
	}
	fill_screen(ctx);
time(2);
	render_minimap(ctx);
}

// t_tex_array	*last_step(t_context *ctx,
// 				double last_step, t_ray *ray, t_vector *last_jump)
// {
// 	if (last_step < ray->h_dist(ray->pos.x))
// 		last_step = ray->v_dist(ray->pos.y) / fabs(ray->dir.y);
// 	else
// 		last_step = ray->h_dist(ray->pos.x) / fabs(ray->dir.x);
// 	last_jump->x = ray->pos.x;
// 	ray->pos.y += last_step * ray->dir.y;
// 	ray->pos.x += last_step * ray->dir.x;
// 	if (!is_wall(ctx, last_jump))
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

// static void	trace_ray_2(t_context *ctx, t_ray *ray, int screen_x)
// {
// 	double			step;
// 	t_tex_array		*texture;
// 	t_vector		tmp;

// 	texture = NULL;
// 	while (on_map(&ctx->map, &ray->pos)
// 		&& ctx->map.matrix[(int)ray->pos.y][(int)ray->pos.x] == '0')
// 	{
// 		step = get_step_size(ray);
// 		tmp.x = ray->pos.x + ray->dir.x * step;
// 		tmp.y = ray->pos.y + ray->dir.y * step;
// 		if (!on_map(&ctx->map, &tmp))
// 		{
// 			printf("Debug: out of map (trace_ray_2)\n");
// 			return ;
// 		}
// 		if (is_wall(ctx, &tmp))
// 		{
// 			texture = last_step(ctx, step, ray, &tmp);
// 			break ;
// 		}
// 		ray->pos.x = tmp.x;
// 		ray->pos.y = tmp.y;
// 	}
// 	if (!on_map(&ctx->map, &ray->pos))
// 		texture = NULL;
// 	display_vertical_slice(ctx, screen_x, ray, texture);
// }

// static void	trace_ray(t_context *ctx, int screen_x)
// {
// 	t_ray	ray;
// 	double	scale_screen_factor;

// 	scale_screen_factor = (double) screen_x * 2 / (double) ctx->width - 1;
// 	ray.dir.x = ctx->player.dir.x + scale_screen_factor * ctx->player.ort.x;
// 	ray.dir.y = ctx->player.dir.y + scale_screen_factor * ctx->player.ort.y;
// 	normalize_vector(&ray.dir);
// 	ray.pos.x = ctx->player.pos.x;
// 	ray.pos.y = ctx->player.pos.y;
// 	if (ray.dir.x > 0)
// 		ray.h_dist = upper_dist;
// 	else
// 		ray.h_dist = lower_dist;
// 	if (ray.dir.y > 0)
// 		ray.v_dist = upper_dist;
// 	else
// 		ray.v_dist = lower_dist;
// 	trace_ray_2(ctx, &ray, screen_x);
// }

// void	render_screen(t_context *ctx)
// {
// 	int	screen_x;
// time(1);
// 	screen_x = 0;
// 	while (screen_x < ctx->width)
// 	{
// 		trace_ray(ctx, screen_x);
// 		screen_x++;
// 	}
// time(2);
// 	render_minimap(ctx);
// }