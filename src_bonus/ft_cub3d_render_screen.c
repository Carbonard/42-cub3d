/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_render_screen.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 17:07:26 by rselva-2          #+#    #+#             */
/*   Updated: 2026/09/07 15:35:02 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	time(int slot, int step)
{
	static size_t	t[10] = {0};
	static size_t	total_time[10] = {0};
	static size_t	cnt[10] = {0};
	static int		first_time[10] = {0};

	if (step == 1)
	{
		t[slot] = get_time();
	}
	else
	{
		cnt[slot]++;
		total_time[slot] += get_time() - t[slot];
		if (cnt[slot] % 100 == 0)
		{
			printf("%d: time mean after %lu iterations: %lf\n", slot, cnt[slot],
				(double)total_time[slot] / cnt[slot]);
			if (!first_time[slot])
			{
				cnt[slot] = 0;
				total_time[slot] = 0;
				first_time[slot] = 1;
			}
		}
	}
}

void	save_walls(t_context *ctx, t_ray_info *ray, t_texture *tex)
{
	int			wall_height;
	int			y_partition;

	wall_height = ctx->height / ray->dist;
	ctx->walls[ray->screen_x].dist = ray->dist;
	ctx->walls[ray->screen_x].texture = tex;
	if (ray->tex.orientation == AXIS_Y)
		ctx->walls[ray->screen_x].tex_x = ray->pos.x - floor(ray->pos.x);
	else
		ctx->walls[ray->screen_x].tex_x = ray->pos.y - floor(ray->pos.y);
	ctx->walls[ray->screen_x].tex_x *= (double)tex->image.width;
	y_partition = (ctx->height - wall_height) * 0.5;
	ctx->walls[ray->screen_x].tex_y = 0;
	if (y_partition <= 0)
		ctx->walls[ray->screen_x].tex_y = (double)
			- y_partition * tex->image.height / wall_height;
	ctx->walls[ray->screen_x].y_step = (double)tex->image.height / wall_height;
	ctx->walls[ray->screen_x].bottom = 0;
	ctx->walls[ray->screen_x].top = ctx->height;
	if (y_partition > 0)
	{
		ctx->walls[ray->screen_x].bottom = y_partition;
		ctx->walls[ray->screen_x].top = ctx->height - y_partition;
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
		return (ctx->textures.door.current);
	else if (ray->tex.type == EXIT)
		return (ctx->textures.exit.current);
	return (NULL);
}

static void	render(t_context *ctx)
{
	time(1, 1);
	render_background(ctx);
	time(1, 2);
	time(2, 1);
	render_walls(ctx);
	time(2, 2);
	time(3, 1);
	render_enemies(ctx);
	time(3, 2);
	render_minimap(ctx);
}

void	trace_ray(t_context *ctx, t_ray_info *ray, t_vector *direction);

void	render_screen(t_context *ctx)
{
	t_ray_info	ray;
	t_vector	direction;
	double		scale_screen_factor;

	time(0, 1);
	ctx->render = 0;
	ray.screen_x = 0;
	while (ray.screen_x < ctx->width)
	{
		scale_screen_factor = (double)(ray.screen_x * 2) / ctx->width - 1;
		direction.x = ctx->player.dir.x
			+ scale_screen_factor * ctx->player.ort.x;
		direction.y = ctx->player.dir.y
			+ scale_screen_factor * ctx->player.ort.y;
		trace_ray(ctx, &ray, &direction);
		save_walls(ctx, &ray, get_texture(ctx, &ray, &direction));
		ray.screen_x++;
	}
	time(0, 2);
	render(ctx);
	if (ctx->pressed.space)
		merge_images(&ctx->screen, &ctx->textures.arm,
			ctx->width / 2, ctx->height / 2);
}
