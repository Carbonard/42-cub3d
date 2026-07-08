/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_render_vertical.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 20:26:17 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/09 00:22:15 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

// This function is an optimization for:
// v_cos(&player->dir, &ray->dir) * dist(&player->pos, &ray->pos)
// static double	screen_dist(t_character *player, t_ray *ray)
// {
// 	return (ray->dist);
// 	return ((player->dir.x * ray->dir.x + player->dir.y * ray->dir.y)
// 				* ray->dist);
// 	// return ((player->dir.x * ray->dir.x + player->dir.y * ray->dir.y)
// 	// 		* sqrt((
// 	// 			((player->pos.x - ray->pos.x)
// 	// 				* (player->pos.x - ray->pos.x))
// 	// 			+ ((player->pos.y - ray->pos.y)
// 	// 				* (player->pos.y - ray->pos.y)))));
// }

static int	texture_coord_x(t_context *ctx,
	t_mlx_image *texture, t_vector *wall_point)
{
	if (!texture)
		return (0);
	if (texture == &ctx->textures.north || texture == &ctx->textures.south)
		return (lower_dist(wall_point->x) * (double)texture->width);
	else
		return (lower_dist(wall_point->y) * (double)texture->width);
}

static double	texture_coord_y(t_context *ctx,
	t_mlx_image *texture, int wall_height, int *y_partition)
{
	*y_partition = (ctx->height - wall_height) * 0.5;
	if (*y_partition > 0)
		return (0);
	return (-(double)(*y_partition) * texture->height / wall_height);
}

// void	display_vertical_slice(t_context *ctx,
// 			t_int_vector *screen, t_ray *ray, t_mlx_image *texture)
// {
// 	int			wall_height;
// 	int			y_discriminant;
// 	t_vector	texture_coord;
// 	double		y_step;

// 	wall_height = ctx->height / (screen_dist(&ctx->player, ray));
// 	texture_coord.x = texture_coord_x(ctx, texture, &ray->pos);
// 	texture_coord.y = texture_coord_y(ctx, texture, wall_height, &y_discriminant);
// 	y_step = (double)texture->height / wall_height;
// 	screen->y = 0;
// 	while (screen->y < ctx->height)
// 	{
// 		if (screen->y <= y_discriminant)
// 			put_pixel(&ctx->screen, screen->x, screen->y, ctx->textures.ceiling);
// 		else if (ctx->height - screen->y <= y_discriminant)
// 			put_pixel(&ctx->screen, screen->x, screen->y, ctx->textures.floor);
// 		else
// 		{
// 			put_pixel(&ctx->screen, screen->x, screen->y,
// 				get_pixel(texture, texture_coord.x, texture_coord.y));
// 			texture_coord.y += y_step;
// 		}
// 		screen->y++;
// 	}
// }

void	display_vertical_slice(t_context *ctx,
			t_int_vector *screen, t_ray *ray, t_mlx_image *texture)
{
	int			wall_height;
	int			y_partition;
	t_vector	texture_coord;
	double		y_step;

	wall_height = ctx->height / ray->dist;//(screen_dist(&ctx->player, ray));
	texture_coord.x = texture_coord_x(ctx, texture, &ray->pos);
	texture_coord.y = texture_coord_y(ctx, texture, wall_height, &y_partition);
	y_step = (double)texture->height / wall_height;
	screen->y = 0;
	while (screen->y <= y_partition)
	{
		put_pixel(&ctx->screen, screen->x, screen->y, ctx->textures.ceiling);
		screen->y++;
	}
	while (ctx->height - screen->y > y_partition && screen->y < ctx->height)
	{
		put_pixel(&ctx->screen, screen->x, screen->y,
			get_pixel(texture, texture_coord.x, texture_coord.y));
		texture_coord.y += y_step;
		if (texture_coord.y < 0)
		{
			printf("y_step: %lf\ny_part: %i\nwall_height: %i\n", y_step, y_partition, wall_height);
			sleep(10);
		}
		screen->y++;
	}
	while (screen->y < ctx->height)
	{
		put_pixel(&ctx->screen, screen->x, screen->y, ctx->textures.floor);
		screen->y++;
	}
}

// static int	texture_coord_x(t_context *ctx,
// 	t_mlx_image *texture, t_vector *wall_point)
// {
// 	if (texture == &ctx->textures.north || texture == &ctx->textures.south)
// 		return (lower_dist(wall_point->x) * (double)texture->width);
// 	else
// 		return (lower_dist(wall_point->y) * (double)texture->width);
// }

// static int	texture_coord_y(t_context *ctx,
// 	t_mlx_image *texture, int wall_height, int screen_y)
// {
// 	return ((screen_y - ((double)ctx->height - wall_height) * 0.5)
// 		* texture->height / wall_height);
// }

// static int	texture_coord_x(t_context *ctx,
// 	t_mlx_image *texture, t_vector *wall_point)
// {
// 	if (texture == &ctx->textures.north || texture == &ctx->textures.south)
// 		return (lower_dist(wall_point->x) * (double)texture->width);
// 	else
// 		return (lower_dist(wall_point->y) * (double)texture->width);
// }

// static int	texture_coord_y(t_context *ctx,
// 	t_mlx_image *texture, int wall_height, int screen_y)
// {
// 	return ((screen_y - ((double)ctx->height - wall_height) * 0.5)
// 		* texture->height / wall_height);
// }

// void	display_vertical_slice(t_context *ctx,
// 			int screen_x, t_ray *ray, t_mlx_image *texture)
// {
// 	int	i;
// 	int	wall_height;
// 	int	y_discriminant;
// 	int	texture_x;

// 	if (!texture)
// 		wall_height = 0;
// 	else
// 	{
// 		wall_height = ctx->height / (screen_dist(&ctx->player, ray));
// 		texture_x = texture_coord_x(ctx, texture, &ray->pos);
// 	}
// 	y_discriminant = (ctx->height - wall_height) * 0.5;
// 	i = 0;
// 	while (i < ctx->height)
// 	{
// 		if (i <= y_discriminant)
// 			put_pixel(&ctx->screen, screen_x, i, ctx->textures.ceiling);
// 		else if (ctx->height - i <= y_discriminant)
// 			put_pixel(&ctx->screen, screen_x, i, ctx->textures.floor);
// 		else
// 		{
// 			put_pixel(&ctx->screen, screen_x, i,
// 				get_pixel(texture,
// 					texture_x,
// 					texture_coord_y(ctx, texture, wall_height, i)));
// 		}
// 		i++;
// 	}
// }
