/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_render_vertical.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 20:26:17 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/06 20:33:04 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

static double	screen_dist(t_character *player, t_ray *ray)
{
	return (v_cos(&player->dir, &ray->dir) * dist(&player->pos, &ray->pos));
}

static int	texture_coord_x(t_context *ctx,
	t_mlx_image *texture, t_vector *wall_point)
{
	if (texture == &ctx->textures.north || texture == &ctx->textures.south)
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

void	display_vertical_slice(t_context *ctx,
			int screen_x, t_ray *ray, t_mlx_image *texture)
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
			put_pixel(&ctx->screen, screen_x, i, ctx->textures.ceiling);
		else if (ctx->height - i <= (ctx->height - wall_height) / 2)
			put_pixel(&ctx->screen, screen_x, i, ctx->textures.floor);
		else
		{
			put_pixel(&ctx->screen, screen_x, i,
				get_pixel(texture,
					texture_coord_x(ctx, texture, &ray->pos),
					texture_coord_y(ctx, texture, wall_height, i)));
		}
		i++;
	}
}
