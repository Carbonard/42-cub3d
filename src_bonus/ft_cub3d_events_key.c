/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_events_key.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 14:06:12 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/04 20:23:11 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	key_press_event(int key, t_context *ctx)
{
	if (key == XK_Escape)
		return (close_game(ctx, 0));
	else if (key == XK_a)
		ctx->pressed.a = 1;
	else if (key == XK_d)
		ctx->pressed.d = 1;
	else if (key == XK_w)
		ctx->pressed.w = 1;
	else if (key == XK_s)
		ctx->pressed.s = 1;
	else if (key == XK_Left)
		ctx->pressed.left = 1;
	else if (key == XK_Right)
		ctx->pressed.right = 1;
	else if (key == XK_r)
	{
		if (!ctx->rain_mode || ctx->rain_mode > 1000)
			ctx->rain_mode = !ctx->rain_mode * 20;
		else
			ctx->rain_mode *= 5;
		render_screen(ctx);
	}
	else
		printf("Invalid key: %d\n", key);
	return (0);
}

int	key_release_event(int key, t_context *ctx)
{
	if (key == XK_a)
		ctx->pressed.a = 0;
	else if (key == XK_d)
		ctx->pressed.d = 0;
	else if (key == XK_w)
		ctx->pressed.w = 0;
	else if (key == XK_s)
		ctx->pressed.s = 0;
	else if (key == XK_Left)
		ctx->pressed.left = 0;
	else if (key == XK_Right)
		ctx->pressed.right = 0;
	return (0);
}

int	loop_hook(t_context *ctx)
{
	static size_t	last_time;
	double			time_increment;
	int				render;

	render = 0;
	if (!last_time)
		last_time = get_time();
	time_increment = (double)(get_time() - last_time) / 100000;
	last_time = get_time();
	if (ctx->pressed.a)
		render = move_player(ctx, 0, -ctx->player.velocity * time_increment);
	if (ctx->pressed.d)
		render = move_player(ctx, 0, +ctx->player.velocity * time_increment);
	if (ctx->pressed.w)
		render = move_player(ctx, +ctx->player.velocity * time_increment, 0);
	if (ctx->pressed.s)
		render = move_player(ctx, -ctx->player.velocity * time_increment, 0);
	if (ctx->pressed.left)
		render = rotate_player(ctx, -ctx->player.ang_velocity * time_increment);
	if (ctx->pressed.right)
		render = rotate_player(ctx, +ctx->player.ang_velocity * time_increment);
	if (render || (ctx->rain_mode && last_time % 1000 == 0))
		render_screen(ctx);
	return (0);
}
