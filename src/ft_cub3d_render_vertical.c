/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_render_vertical.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 20:26:17 by rselva-2          #+#    #+#             */
/*   Updated: 2026/08/05 18:27:51 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

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
	return ((-(double)(*y_partition)) * texture->height / wall_height);
}

void	display_vertical_slice(t_context *ctx,
			t_int_vector *screen, t_ray *ray, t_mlx_image *texture)
{
	int			wall_height;
	int			y_partition;
	t_vector	texture_coord;
	double		y_step;

	wall_height = ctx->height / ray->dist;
	texture_coord.x = texture_coord_x(ctx, texture, &ray->pos);
	texture_coord.y = texture_coord_y(ctx, texture, wall_height, &y_partition);
	y_step = (double)texture->height / wall_height;
	screen->y = 0;
	while (screen->y <= y_partition)
	{
		put_pixel(&ctx->screen, screen->x, screen->y, ctx->textures.ceiling);
		put_pixel(&ctx->screen, screen->x, ctx->height - screen->y,
			ctx->textures.floor);
		screen->y++;
	}
	while (ctx->height - screen->y > y_partition && screen->y < ctx->height)
	{
		put_pixel(&ctx->screen, screen->x, screen->y,
			get_pixel(texture, texture_coord.x, texture_coord.y));
		texture_coord.y += y_step;
		screen->y++;
	}
}
