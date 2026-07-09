/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_render_vertical.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 20:26:17 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/09 23:44:47 by rselva-2         ###   ########.fr       */
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

void	save_walls(t_context *ctx,
			t_int_vector *screen, t_ray *ray, t_texture *texture)
{
	int			wall_height;
	int			y_partition;

	wall_height = ctx->height / ray->dist;
	ctx->w_limits[screen->x].texture = texture;
// ctx->w_limits[screen->x].tex_x = texture_coord_x(ctx, texture, &ray->pos);
	if (texture == ctx->textures.north.current || texture == ctx->textures.south.current)
		ctx->w_limits[screen->x].tex_x = lower_dist(ray->pos.x);
	else
		ctx->w_limits[screen->x].tex_x = lower_dist(ray->pos.y);
	ctx->w_limits[screen->x].tex_x *= (double)texture->image.width;
// ctx->w_limits[screen->x].tex_y = texture_coord_y(ctx, &texture->image, wall_height, &y_partition);
	y_partition = (ctx->height - wall_height) * 0.5;
	ctx->w_limits[screen->x].tex_y = 0;
	if (y_partition <= 0)
		ctx->w_limits[screen->x].tex_y = -(double)(y_partition) * texture->image.height / wall_height;
	ctx->w_limits[screen->x].y_step = (double)texture->image.height / wall_height;
	ctx->w_limits[screen->x].bottom = 0;
	ctx->w_limits[screen->x].top = ctx->height;
	if (y_partition > 0)
	{
		ctx->w_limits[screen->x].bottom = y_partition;
		ctx->w_limits[screen->x].top = ctx->height - y_partition;
	}
	return;
}

void put_floor_and_ceiling(t_context *ctx, t_int_vector *screen, t_vector *floor_point)
{
	const t_texture		*floor = ctx->textures.floor.current;
	const t_texture		*ceiling = ctx->textures.ceiling.current;

	if (!floor->image.img)
		put_pixel(&ctx->screen, screen->x, screen->y, floor->color);
	if (!ceiling->image.img)
		put_pixel(&ctx->screen, screen->x, ctx->height - screen->y, ceiling->color);
	if (floor_point->x < 0 || floor_point->y < 0 || floor_point->x > ctx->width || floor_point->y > ctx->height)
		return ;
	if (ceiling->image.img)
		put_pixel(&ctx->screen, screen->x, screen->y,
			get_pixel(&ceiling->image,
			(floor_point->x - (int)(floor_point->x)) * ceiling->image.width,
			(floor_point->y - (int)(floor_point->y)) * ceiling->image.height));
	if (floor->image.img)
		put_pixel(&ctx->screen, screen->x, ctx->height - screen->y,
			get_pixel(&floor->image,
			(floor_point->x - (int)(floor_point->x)) * floor->image.width,
			(floor_point->y - (int)(floor_point->y)) * floor->image.height));
}

void	fill_background(t_context *ctx)
{
	t_int_vector		screen;
	t_vector			floor_point;
	double				dist;
	const double				x_step = (double) 2 / ctx->width;

	screen.y = 0;
	while (screen.y < ctx->height / 2)
	{
		dist = (double) ctx->height / (ctx->height - screen.y * 2);
		screen.x = 0;
		floor_point.x = ctx->player.pos.x 
			+ (ctx->player.dir.x - ctx->player.ort.x) * dist;
		floor_point.y = ctx->player.pos.y 
			+ (ctx->player.dir.y - ctx->player.ort.y) * dist;
		while (screen.x < ctx->width)
		{
			floor_point.x += x_step * ctx->player.ort.x * dist;
			floor_point.y += x_step * ctx->player.ort.y * dist;
			put_floor_and_ceiling(ctx, &screen, &floor_point);
			screen.x++;
		}
		screen.y++;
	}
}

void	fill_screen(t_context *ctx)
{
	t_int_vector	screen;
	t_vector		tex;
	double			y_step;
	t_texture		*texture;

	fill_background(ctx);
	screen.x = 0;
	while (screen.x < ctx->width)
	{
		tex.x = ctx->w_limits[screen.x].tex_x;
		tex.y = ctx->w_limits[screen.x].tex_y;
		texture = ctx->w_limits[screen.x].texture;
		y_step = ctx->w_limits[screen.x].y_step;
		screen.y = ctx->w_limits[screen.x].bottom + 1;
		while (screen.y < ctx->w_limits[screen.x].top)
		{
			put_pixel(&ctx->screen, screen.x, screen.y,
				get_pixel(&texture->image, tex.x, tex.y));
			tex.y += y_step;
			screen.y++;
		}
		screen.x++;
	}
}

