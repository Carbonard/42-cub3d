/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_render_vertical.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 20:26:17 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/15 22:30:34 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

// static int	texture_coord_x(t_context *ctx,
// 	t_texture *texture, t_vector *wall_point)
// {
// 	if (texture == ctx->textures.north.current || texture == ctx->textures.south.current)
// 		return (lower_dist(wall_point->x) * (double)texture->image.width);
// 	else
// 		return (lower_dist(wall_point->y) * (double)texture->image.width);
// }

// // static int	texture_coord_y(t_context *ctx,
// // 	t_tex_array *texture, int wall_height, int screen_y)
// // {
// // 	return ((screen_y - ((double)ctx->height - wall_height) / 2)
// // 		* texture->tex[ctx->current_tex % texture->size].image.height / wall_height);
// // }

// static double	texture_coord_y(t_context *ctx,
// 	t_mlx_image *texture, int wall_height, int *y_partition)
// {
// 	*y_partition = (ctx->height - wall_height) * 0.5;
// 	if (*y_partition > 0)
// 		return (0);
// 	return (-(double)(*y_partition) * texture->height / wall_height);
// }

// static double floor_dist_to_screen(t_context *ctx, int screen_y)
// {
// 	static double	cache[2048];
// 	static int		height;
// 	int				y;

// 	if (height != ctx->height)
// 	{
// 		height = ctx->height;
// 		y = 0;
// 		while (y < height)
// 		{
// 			cache[y] = (double) height / (height - y * 2);
// 			y++;
// 		}	
// 	}
// 	return (cache[screen_y]);
// }

// static double floor_dist_ortogonal(t_context *ctx, int screen_x)
// {
// 	static double	cache[2048];
// 	static int		width;
// 	int				x;

// 	if (width != ctx->width)
// 	{
// 		width = ctx->width;
// 		x = 0;
// 		while (x < width)
// 		{
// 			cache[x] = (double) x * 2 / width - 1;
// 			x++;
// 		}
// 	}
// 	return (cache[screen_x]);
// }

// static void screen_to_map(t_context *ctx, t_vector *floor_pos, int screen_x, int screen_y)
// {
// 	double	dist;
// 	double	s_x;

// 	dist = (double) ctx->height / (ctx->height - screen_y * 2);
// 	s_x = (double) screen_x * 2 / ctx->width - 1;
// 	floor_pos->x = ctx->player.pos.x
// 		+ ctx->player.ort.x * s_x
// 		+ ctx->player.dir.x * dist;
// 	floor_pos->y = ctx->player.pos.y
// 		+ ctx->player.ort.y * s_x
// 		+ ctx->player.dir.y * dist;
// }

// LSD
// static unsigned int	get_floor_color(t_context *ctx,
// 	t_mlx_image *texture, t_ray *wall_point, int screen_y)
// {
// 	t_vector	floor_point;
// 	unsigned int	color;

// 	get_floor_position(ctx, &floor_point, wall_point, screen_y);
// 	color = get_pixel(texture,
// 		lower_dist(floor_point.x) * texture->width,
// 		lower_dist(floor_point.y) * texture->height);
// 	return (color);
// }

// static unsigned int	get_floor_ceiling_color(t_context *ctx,
// 	t_texture *texture, int screen_x, int screen_y)
// {
// 	t_vector		floor_point;
// 	double			dist;
// 	static double	s_x;
// 	static int		cache_x;

// 	if (!texture->image.img)
// 		return (texture->color);
// 	dist = (double) ctx->height / (double) (ctx->height - screen_y * 2);
// 	if (cache_x != screen_x)
// 	{
// 		s_x = ((double) screen_x * 2 / ctx->width - 1);
// 		cache_x = screen_x;
// 	}
// 	floor_point.x = ctx->player.pos.x
// 		+ (ctx->player.ort.x * s_x + ctx->player.dir.x) * dist;
// 	floor_point.y = ctx->player.pos.y
// 		+ (ctx->player.ort.y * s_x + ctx->player.dir.y) * dist;
// 	// screen_to_map(ctx, &floor_point, screen_x, screen_y);
// 	return (get_pixel(&texture->image,
// 		(floor_point.x - (int) floor_point.x) * texture->image.width,
// 		(floor_point.y - (int) floor_point.y) * texture->image.height));
// 	// if (((int)(floor_point.x * 2) * 1031 / (int)(floor_point.y * 2 + 2)) % 50 == 0)
// 	// 	return (rgb(50,50,30));
// }

// void	display_vertical(t_context *ctx,
// 			t_int_vector *screen, t_ray *ray, t_texture *texture)
// {
// 	int			wall_height;
// 	int			y_partition;
// 	t_vector	tex;
// 	double		y_step;

// 	wall_height = ctx->height / ray->dist;
// 	tex.x = texture_coord_x(ctx, texture, &ray->pos);
// 	tex.y = texture_coord_y(ctx, &texture->image, wall_height, &y_partition);
// 	y_step = (double)texture->image.height / wall_height;
// 	while (screen->y < ctx->height)
// 	{
// 		if (ctx->rain_mode && get_time() % ctx->rain_mode == 0)
// 			put_pixel(&ctx->screen, screen->x, screen->y, rgb(16, 71, 192));
// 		else if (screen->y <= y_partition)
// 			put_pixel(&ctx->screen, screen->x, screen->y, get_floor_ceiling_color(ctx, ctx->textures.ceiling.current, screen->x, screen->y));
// 		else if (ctx->height - screen->y <= y_partition)
// 			put_pixel(&ctx->screen, screen->x, screen->y, get_floor_ceiling_color(ctx, ctx->textures.floor.current, screen->x, ctx->height - screen->y));
// 		else
// 		{
// 			put_pixel(&ctx->screen, screen->x, screen->y,
// 				get_pixel(&texture->image,
// 					tex.x, tex.y));
// 			tex.y += y_step;
// 		}
// 		screen->y++;
// 	}
// }




// static int	texture_coord_x(t_context *ctx,
// 	t_texture *texture, t_vector *wall_point)
// {
// 	if (texture == ctx->textures.north.current || texture == ctx->textures.south.current)
// 		return (lower_dist(wall_point->x) * (double)texture->image.width);
// 	else
// 		return (lower_dist(wall_point->y) * (double)texture->image.width);
// }

// static double	texture_coord_y(t_context *ctx,
// 	t_mlx_image *texture, int wall_height, int *y_partition)
// {
// 	*y_partition = (ctx->height - wall_height) * 0.5;
// 	if (*y_partition > 0)
// 		return (0);
// 	return (-(double)(*y_partition) * texture->height / wall_height);
// }


void	merge_enemy_images(t_context *ctx, t_mlx_image *other, t_enemy *enemy)
{
	int			i;
	int			j;
	t_vector	resize;

	resize.x = (double)other->width / (double)enemy->size;
	resize.y = (double)other->height / (double)enemy->size;
	j = fmax(0, -enemy->screen_pos.y);
	while (j < enemy->size && j + enemy->screen_pos.y < ctx->height)
	{
		i = fmax(0, -enemy->screen_pos.x);
		while (i < enemy->size && i + enemy->screen_pos.x < ctx->width)
		{
			if (enemy->screen_pos.x + i < ctx->width
				&& enemy->dist <= ctx->walls[enemy->screen_pos.x + i].dist)
				put_pixel(&ctx->screen,
					enemy->screen_pos.x + i, enemy->screen_pos.y + j,
					merge_colors(
						get_pixel(&ctx->screen,
							enemy->screen_pos.x + i, enemy->screen_pos.y + j),
						get_pixel(other, resize.x * i, resize.y * j)));
			i++;
		}
		j++;
	}
}

void	fill_enemy_info(t_context *ctx, t_enemy *enemy)
{
	t_vector	dir;
	double		cos;
	double		screen_factor;

	dir.x = enemy->map.x - ctx->player.pos.x;
	dir.y = enemy->map.y - ctx->player.pos.y;
	cos = v_cos(&ctx->player.dir, &dir);
	enemy->dist = dist(&ctx->player.pos, &enemy->map) * cos;
	enemy->size = (float)ctx->height / (enemy->dist);
	if (ctx->player.dir.x * dir.y < ctx->player.dir.y * dir.x)
		cos *= -1;
	screen_factor = sqrt(1 - cos * cos) / cos;
	enemy->screen_pos.x = (screen_factor + 1) * ctx->width / 2 - enemy->size / 2;
	enemy->screen_pos.y = (ctx->height - enemy->size) / 2;
	if (enemy->type == ENEMY)
		enemy->texture = ctx->textures.enemy.current;
	else
		enemy->texture = enemy->explosion->texture;
}

void	sort_enemies(t_context *ctx)
{
	int		i;
	int		j;
	t_enemy	temp;

	i = 0;
	while (i < ctx->n_enemies)
	{
		j = i + 1;
		while (j < ctx->n_enemies)
		{
			if (ctx->enemies[i].dist < ctx->enemies[j].dist)
			{
				ft_memmove(&temp, &ctx->enemies[i], sizeof(t_enemy));
				ft_memmove(&ctx->enemies[i], &ctx->enemies[j], sizeof(t_enemy));
				ft_memmove(&ctx->enemies[j], &temp, sizeof(t_enemy));
			}
			j++;
		}
		i++;
	}
}

void	check_explosions(t_context *ctx)
{
	int	i;
	int	tex;

	i = 0;
	while (i < ctx->n_explosions)
	{
		if (ctx->explosions[i].time)
		{
			tex = (get_time() - ctx->explosions[i].time) / 150000;
			if (tex < ctx->textures.explosion.size)
				ctx->explosions[i].texture = &ctx->textures.explosion.tex[tex];
			else
				ctx->map.matrix[ctx->explosions[i].map.y][ctx->explosions[i].map.x] = FLOOR;
			ctx->render = 1;
		}
		i++;
	}
}

void	render_enemies(t_context *ctx)
{
	int	i;

	check_explosions(ctx);
	i = 0;
	while (i < ctx->n_enemies)
	{
		fill_enemy_info(ctx, &ctx->enemies[i]);
		i++;
	}
	sort_enemies(ctx);
	i = 0;
	while (i < ctx->n_enemies)
	{
		merge_enemy_images(ctx, &ctx->enemies[i].texture->image, &ctx->enemies[i]);
		i++;
	}
	ctx->n_enemies = 0;
}

