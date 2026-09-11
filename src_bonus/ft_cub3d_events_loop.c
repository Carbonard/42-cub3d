/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_events_loop.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 19:11:22 by rselva-2          #+#    #+#             */
/*   Updated: 2026/09/12 00:48:56 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	run_spaces(t_context *ctx, size_t last_time)
{
	if (ctx->pressed.space && last_time - ctx->last_time_shot > 500000)
	{
		shoot(ctx);
		ctx->last_time_shot = last_time;
		ctx->render = 1;
	}
	if (!ctx->pressed.space)
		ctx->last_time_shot = 0;
}

void	run_game(t_context *ctx, size_t last_time, double t_increm)
{
	static size_t	texture_render_time;

	ctx->render |= check_mouse(ctx);
	if (ctx->pressed.a)
		ctx->render |= move_player(ctx, 0, -ctx->player.velocity * t_increm);
	if (ctx->pressed.d)
		ctx->render |= move_player(ctx, 0, +ctx->player.velocity * t_increm);
	if (ctx->pressed.w)
		ctx->render |= move_player(ctx, +ctx->player.velocity * t_increm, 0);
	if (ctx->pressed.s)
		ctx->render |= move_player(ctx, -ctx->player.velocity * t_increm, 0);
	if (ctx->pressed.left)
		ctx->render |= rotate_player(ctx, -ctx->player.rot_velocity * t_increm);
	if (ctx->pressed.right)
		ctx->render |= rotate_player(ctx, +ctx->player.rot_velocity * t_increm);
	if (last_time - texture_render_time > 150000)
	{
		texture_render_time = last_time;
		ctx->current_tex++;
		set_textures(ctx);
		ctx->render = 1;
	}
	run_spaces(ctx, last_time);
}

void	measure_fps(t_context *ctx, int f)
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
		ctx->render = 1;
	}
	frames += f;
}

void	render_game(t_context *ctx)
{
	static size_t	last_render;

	if (ctx->render
		&& ctx->mode == GAME
		&& get_time() > last_render + ctx->usec_per_frame)
	{
		render_screen(ctx);
		last_render = get_time();
		measure_fps(ctx, 1);
	}
	else
	{
		usleep(1000);
		measure_fps(ctx, 0);
	}
}

int	loop_hook(t_context *ctx)
{
	static size_t	last_time;
	double			time_increment;

	if (!last_time)
		last_time = get_time();
	time_increment = (double)(get_time() - last_time) / 100000;
	ctx->time += time_increment;
	last_time = get_time();
	if (ctx->mode == MENU)
	{
		open_menu(ctx);
		return (0);
	}
	if (ctx->mode == CONFIG)
	{
		open_config(ctx);
		return (0);
	}
	run_game(ctx, last_time, time_increment);
	render_game(ctx);
	return (0);
}
