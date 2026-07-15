/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_render_screen.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 17:07:26 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/15 19:02:17 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void time(int slot, int step)
{
	static size_t t[10] = {0};
	static size_t total_time[10] = {0};
	static size_t cnt[10] = {0};
	static int first_time[10] = {0};

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
			printf("%d: time mean after %lu iterations: %lf\n", slot, cnt[slot], (double)total_time[slot] / cnt[slot]);
			if (!first_time[slot])
			{
				cnt[slot] = 0;
				total_time[slot] = 0;
				first_time[slot] = 1;
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
		return (ctx->textures.door.current);
	else if (ray->tex.type == EXIT)
		return (ctx->textures.exit.current);
	return (NULL);
}

static void	save_enemy(t_context *ctx, t_int_vector *cell)
{
	int	i;

	i = 0;
	while (i < ctx->n_enemies)
	{
		if ((int)ctx->enemies[i].map.x == cell->x && (int)ctx->enemies[i].map.y == cell->y)
			return ;
		i++;
	}
	ctx->enemies[ctx->n_enemies].map.x = cell->x + 0.5;
	ctx->enemies[ctx->n_enemies].map.y = cell->y + 0.5;
	ctx->n_enemies++;
}

static void	trace_ray(t_context *ctx, t_ray_info *ray, t_vector *direction)
{
	t_ray_cast	rc;

	init_ray_casting(ctx, &rc, direction);
	while (ctx->map.matrix[rc.map_cell.y][rc.map_cell.x] != WALL
		&& ctx->map.matrix[rc.map_cell.y][rc.map_cell.x] != CLOSED_DOOR
		&& ctx->map.matrix[rc.map_cell.y][rc.map_cell.x] != EXIT)
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
		if (ctx->map.matrix[rc.map_cell.y][rc.map_cell.x] == ENEMY)
			save_enemy(ctx, &rc.map_cell);
	}
	ray->tex.type = ctx->map.matrix[rc.map_cell.y][rc.map_cell.x];
	ray->pos.x = ctx->player.pos.x + direction->x * ray->dist;
	ray->pos.y = ctx->player.pos.y + direction->y * ray->dist;
	save_walls(ctx, ray, get_texture(ctx, ray, direction));
}

void	measure_fps(t_context *ctx)
{
	static int		frames;
	static size_t	last_time;
	size_t			current_time;

	current_time = get_time();
	if ((current_time - last_time) / 1000000 > 1)
	{
		ctx->fps = frames;
		last_time = current_time;
		frames = 0;
	}
	frames++;
}

void	render_screen(t_context *ctx)
{
	t_ray_info	ray;
	t_vector	direction;
	double	scale_screen_factor;

	measure_fps(ctx);
time(0,1);
	render_background(ctx);
time(0,2);
time(1,1);
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
time(1,2);
time(2,1);
	render_walls(ctx);
time(2,2);
time(3,1);
	render_enemies(ctx);
time(3,2);
	render_minimap(ctx);
}
