/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_events_key.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 14:06:12 by rselva-2          #+#    #+#             */
/*   Updated: 2026/08/10 11:35:40 by rselva-2         ###   ########.fr       */
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
	double			time_jump;
	int				render;

	render = 0;
	time_jump = !!last_time * (double)(get_time() - last_time) / 100000;
	if (time_jump > 1)
		time_jump = 1;
	last_time = get_time();
	if (ctx->pressed.a)
		render = move_player(ctx, 0, -ctx->player.velocity * time_jump);
	if (ctx->pressed.d)
		render = move_player(ctx, 0, +ctx->player.velocity * time_jump);
	if (ctx->pressed.w)
		render = move_player(ctx, +ctx->player.velocity * time_jump, 0);
	if (ctx->pressed.s)
		render = move_player(ctx, -ctx->player.velocity * time_jump, 0);
	if (ctx->pressed.left)
		render = rotate_player(ctx, -ctx->player.rot_velocity * time_jump);
	if (ctx->pressed.right)
		render = rotate_player(ctx, +ctx->player.rot_velocity * time_jump);
	if (render)
		render_screen(ctx);
	return (0);
}
