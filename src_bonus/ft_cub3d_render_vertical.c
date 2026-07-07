/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_render_vertical.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 20:26:17 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/07 18:51:47 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

static int	texture_coord_x(t_context *ctx,
	t_mlx_image *texture, t_vector *wall_point)
{
	if (texture == &ctx->textures.north.image || texture == &ctx->textures.south.image)
		return (lower_dist(wall_point->x) * (double)texture->width);
	else
		return (lower_dist(wall_point->y) * (double)texture->width);
}

static int	texture_coord_y(t_context *ctx,
	t_mlx_image *texture, int wall_height, int screen_y)
{
	return ((screen_y - ((double)ctx->height - wall_height) / 2)
		* texture->height / wall_height);
}

static void screen_to_map(t_context *ctx, t_vector *floor_pos, int screen_x, int screen_y)
{
	double	floor_dist_to_screen;

	floor_dist_to_screen = (double) ctx->height / (ctx->height - screen_y * 2);
	double	s_x = ((double) screen_x * 2 / ctx->width - 1) * floor_dist_to_screen;
	floor_pos->x = ctx->player.pos.x + ctx->player.ort.x * s_x + ctx->player.dir.x * floor_dist_to_screen;
	floor_pos->y = ctx->player.pos.y + ctx->player.ort.y * s_x + ctx->player.dir.y * floor_dist_to_screen;
}

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

static unsigned int	get_floor_ceiling_color(t_context *ctx,
	t_texture *texture, int screen_x, int screen_y)
{
	t_vector	floor_point;

	if (!texture->image.img)
		return (texture->color);
	screen_to_map(ctx, &floor_point, screen_x, screen_y);
	return (get_pixel(&texture->image,
		lower_dist(floor_point.x) * texture->image.width,
		lower_dist(floor_point.y) * texture->image.height));
	// if (((int)(floor_point.x * 2) * 1031 / (int)(floor_point.y * 2 + 2)) % 50 == 0)
	// 	return (rgb(50,50,30));
}

void	display_vertical_slice(t_context *ctx,
			int screen_x, t_ray *ray, t_texture *texture)
{
	int				i;
	int				wall_height;

	if (!texture)
	{
		printf("Debug: missing texture (display_vertical_slice)\n");
		return ;
	}
	i = 0;
	wall_height = ctx->height / (screen_dist(&ctx->player, ray));
	while (i < ctx->height)
	{
		if (ctx->rain_mode && get_time() % ctx->rain_mode == 0)
			put_pixel(&ctx->screen, screen_x, i, rgb(16, 71, 192));
		else if (i <= (ctx->height - wall_height) / 2)
			put_pixel(&ctx->screen, screen_x, i, get_floor_ceiling_color(ctx, &ctx->textures.ceiling, screen_x, i));
		else if (ctx->height - i <= (ctx->height - wall_height) / 2)
			put_pixel(&ctx->screen, screen_x, i, get_floor_ceiling_color(ctx, &ctx->textures.floor, screen_x, ctx->height - i));
		else
		{
			put_pixel(&ctx->screen, screen_x, i,
				get_pixel(&texture->image,
					texture_coord_x(ctx, &texture->image, &ray->pos),
					texture_coord_y(ctx, &texture->image, wall_height, i)));
		}
		i++;
	}
}
