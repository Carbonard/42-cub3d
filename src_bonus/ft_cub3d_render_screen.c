/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_render_screen.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 17:07:26 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/15 23:46:45 by rselva-2         ###   ########.fr       */
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

void	save_walls(t_context *ctx, t_ray_info *ray, t_texture *tex)
{
	int			wall_height;
	int			y_partition;

	wall_height = ctx->height / ray->dist;
	ctx->walls[ray->screen_x].dist = ray->dist;
	ctx->walls[ray->screen_x].texture = tex;
// ctx->walls[screen->x].tex_x = texture_coord_x(ctx, texture, &ray->pos);
	if (ray->tex.orientation == AXIS_Y)
		ctx->walls[ray->screen_x].tex_x = ray->pos.x - floor(ray->pos.x);
	else
		ctx->walls[ray->screen_x].tex_x = ray->pos.y - floor(ray->pos.y);
	ctx->walls[ray->screen_x].tex_x *= (double)tex->image.width;
// ctx->walls[screen->x].tex_y = texture_coord_y(ctx, &texture->image, wall_height, &y_partition);
	y_partition = (ctx->height - wall_height) * 0.5;
	ctx->walls[ray->screen_x].tex_y = 0;
	if (y_partition <= 0)
		ctx->walls[ray->screen_x].tex_y = -(double)(y_partition) * tex->image.height / wall_height;
	ctx->walls[ray->screen_x].y_step = (double)tex->image.height / wall_height;
	ctx->walls[ray->screen_x].bottom = 0;
	ctx->walls[ray->screen_x].top = ctx->height;
	if (y_partition > 0)
	{
		ctx->walls[ray->screen_x].bottom = y_partition;
		ctx->walls[ray->screen_x].top = ctx->height - y_partition;
	}
	return;
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

static t_explosion	*save_explosion(t_context *ctx, t_int_vector *cell)
{
	int	i;

	i = 0;
	while (i < ctx->n_explosions)
	{
		if (ctx->explosions[i].map.x == cell->x && ctx->explosions[i].map.y == cell->y)
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
		if ((int)ctx->enemies[i].map.x == cell->x && (int)ctx->enemies[i].map.y == cell->y)
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
		if (ctx->map.matrix[rc.map_cell.y][rc.map_cell.x] == ENEMY
			|| ctx->map.matrix[rc.map_cell.y][rc.map_cell.x] == EXPLOSION)
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
	if ((current_time - last_time) / 1000000 >= 1)
	{
		ctx->real_fps = frames;
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
time(0,2);
time(1,1);
	render_background(ctx);
time(1,2);
time(2,1);
	render_walls(ctx);
time(2,2);
time(3,1);
	render_enemies(ctx);
time(3,2);
	render_minimap(ctx);
}
