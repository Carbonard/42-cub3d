/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_render_screen.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 17:07:26 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/08 01:16:45 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

t_tex_array	*last_step(t_context *ctx,
				double last_step, t_ray *ray, t_vector *last_jump)
{
	if (last_step < ray->h_dist(ray->pos.x))
		last_step = ray->v_dist(ray->pos.y) / fabs(ray->dir.y);
	else
		last_step = ray->h_dist(ray->pos.x) / fabs(ray->dir.x);
	last_jump->x = ray->pos.x;
	ray->pos.y += last_step * ray->dir.y;
	ray->pos.x += last_step * ray->dir.x;
	if (!is_wall(ctx, last_jump))
	{
		if (ray->dir.x > 0)
			return (&ctx->textures.east);
		else
			return (&ctx->textures.west);
	}
	else
	{
		if (ray->dir.y > 0)
			return (&ctx->textures.south);
		else
			return (&ctx->textures.north);
	}
}

static void	trace_ray_2(t_context *ctx, t_ray *ray, int screen_x)
{
	double			step;
	t_tex_array		*texture;
	t_vector		tmp;

	texture = NULL;
	while (on_map(&ctx->map, &ray->pos)
		&& ctx->map.matrix[(int)ray->pos.y][(int)ray->pos.x] == '0')
	{
		step = get_step_size(ray);
		tmp.x = ray->pos.x + ray->dir.x * step;
		tmp.y = ray->pos.y + ray->dir.y * step;
		if (!on_map(&ctx->map, &tmp))
		{
			printf("Debug: out of map (trace_ray_2)\n");
			return ;
		}
		if (is_wall(ctx, &tmp))
		{
			texture = last_step(ctx, step, ray, &tmp);
			break ;
		}
		ray->pos.x = tmp.x;
		ray->pos.y = tmp.y;
	}
	if (!on_map(&ctx->map, &ray->pos))
		texture = NULL;
	display_vertical_slice(ctx, screen_x, ray, texture);
}

static void	trace_ray(t_context *ctx, int screen_x)
{
	t_ray	ray;
	double	scale_screen_factor;

	scale_screen_factor = (double) screen_x * 2 / (double) ctx->width - 1;
	ray.dir.x = ctx->player.dir.x + scale_screen_factor * ctx->player.ort.x;
	ray.dir.y = ctx->player.dir.y + scale_screen_factor * ctx->player.ort.y;
	normalize_vector(&ray.dir);
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
	trace_ray_2(ctx, &ray, screen_x);
}

void	render_screen(t_context *ctx)
{
	int	screen_x;

	screen_x = 0;
	while (screen_x < ctx->width)
	{
		trace_ray(ctx, screen_x);
		screen_x++;
	}
	render_minimap(ctx);
}
