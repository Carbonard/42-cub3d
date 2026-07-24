/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_render_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 20:28:43 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/16 22:47:11 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

static void put_floor_and_ceiling(t_context *ctx, t_int_vector *screen, t_vector *floor_point)
{
	const t_texture		*floor = ctx->textures.floor.current;
	const t_texture		*ceiling = ctx->textures.ceiling.current;

	// if (floor_point->x < 0 || floor_point->y < 0 || floor_point->x > ctx->width || floor_point->y > ctx->height)
	// 	return ;
	if (!ceiling->image.img)
		put_pixel(&ctx->screen, screen->x, screen->y, ceiling->color);
	else
		put_pixel(&ctx->screen, screen->x, screen->y,
			get_pixel(&ceiling->image,
			floor_point->x * ceiling->image.width,
			floor_point->y * ceiling->image.height));
	if (!floor->image.img)
		put_pixel(&ctx->screen, screen->x, ctx->height - screen->y, floor->color);
	else
		put_pixel(&ctx->screen, screen->x, ctx->height - screen->y,
			get_pixel(&floor->image,
			floor_point->x * floor->image.width,
			floor_point->y * floor->image.height));
}

void	render_background(t_context *ctx)
{
	t_int_vector		screen;
	t_vector			floor_point;
	double				dist;
	const double		x_step = (double) 2 / ctx->width;
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
			floor_point.x -= floor(floor_point.x);
			floor_point.y += x_step * ctx->player.ort.y * dist;
			floor_point.y -= floor(floor_point.y);
			if (ctx->walls[screen.x].bottom >= screen.y)
				put_floor_and_ceiling(ctx, &screen, &floor_point);
			screen.x++;
		}
		screen.y++;
	}
}

void	render_walls(t_context *ctx)
{
	t_int_vector	screen;
	t_vector		tex;
	double			y_step;
	t_texture		*texture;

	screen.x = 0;
	while (screen.x < ctx->width)
	{
		tex.x = ctx->walls[screen.x].tex_x;
		tex.y = ctx->walls[screen.x].tex_y;
		texture = ctx->walls[screen.x].texture;
		y_step = ctx->walls[screen.x].y_step;
		screen.y = ctx->walls[screen.x].bottom + 1;
		while (screen.y < ctx->walls[screen.x].top)
		{
			if (texture->image.img)
				put_pixel(&ctx->screen, screen.x, screen.y,
					get_pixel(&texture->image, tex.x, tex.y));
			else
				put_pixel(&ctx->screen, screen.x, screen.y, texture->color);
			tex.y += y_step;
			screen.y++;
		}
		screen.x++;
	}
}
