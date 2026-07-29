/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_events_key.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 14:06:12 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/29 05:47:14 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	menu_key_events(t_context *ctx, int key)
{
	if (key == XK_Up)
		ctx->focus = (ctx->focus + B_SIZE - 1) % B_SIZE;
	else if (key == XK_Down)
		ctx->focus = (ctx->focus + 1) % B_SIZE;
	else if (key == XK_space || key == 65293)
		ctx->buttons[ctx->focus].action(ctx);
	else
	{
		printf("Invalid key: %d\n", key);
		return ;
	}
	ctx->render = 1;
}

void	config_key_events(t_context *ctx, int key)
{
	if (key == XK_Up)
		ctx->config_focus = (ctx->config_focus + C_SIZE - 1) % C_SIZE;
	else if (key == XK_Down)
		ctx->config_focus = (ctx->config_focus + 1) % C_SIZE;
	else if (key == XK_space || key == 65293)
		open_menu(ctx);
	else if (key == XK_Left)
		ctx->config_buttons[ctx->config_focus].config->setter(ctx, ctx->config_buttons[ctx->config_focus].config->current - 1);
	else if (key == XK_Right)
		ctx->config_buttons[ctx->config_focus].config->setter(ctx, ctx->config_buttons[ctx->config_focus].config->current + 1);
	else
	{
		printf("Invalid key: %d\n", key);
		return ;
	}
	ctx->render = 1;
}

int	key_press_event(int key, t_context *ctx)
{
	if (key == XK_Escape)
		return (close_game(ctx, 0));
	else if (key == XK_m)
	{
		ctx->mode = MENU;
		ctx->render = 1;
	}
	else if (ctx->mode == MENU)
		menu_key_events(ctx, key);
	else if (ctx->mode == CONFIG)
		config_key_events(ctx, key);
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
	else if (key == XK_space)
		ctx->pressed.space = 1;
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
	else if (key == XK_space)
	{
		ctx->pressed.space = 0;
		ctx->render = 1;
	}
	return (0);
}

void	run_game(t_context *ctx, size_t last_time, double time_increment)
{
	static size_t	texture_render_time;

	ctx->render |= check_mouse(ctx);
	if (ctx->pressed.a)
		ctx->render |= move_player(ctx, 0, -ctx->player.velocity * time_increment);
	if (ctx->pressed.d)
		ctx->render |= move_player(ctx, 0, +ctx->player.velocity * time_increment);
	if (ctx->pressed.w)
		ctx->render |= move_player(ctx, +ctx->player.velocity * time_increment, 0);
	if (ctx->pressed.s)
		ctx->render |= move_player(ctx, -ctx->player.velocity * time_increment, 0);
	if (ctx->pressed.left)
		ctx->render |= rotate_player(ctx, -ctx->player.rotation_velocity * time_increment);
	if (ctx->pressed.right)
		ctx->render |= rotate_player(ctx, +ctx->player.rotation_velocity * time_increment);
	if (last_time - texture_render_time > 150000 * 1000)
	{
		texture_render_time = last_time;
		ctx->current_tex++;
		set_textures(ctx);
		ctx->render |= 1;
	}
	if (ctx->pressed.space && last_time - ctx->last_time_shot > 500000)
	{
		shoot(ctx);
		ctx->last_time_shot = last_time;
		ctx->render = 1;
	}
	if (!ctx->pressed.space)
		ctx->last_time_shot = 0;
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

int	loop_hook(t_context *ctx)
{
	static size_t	last_time;
	double			time_increment;
	static size_t	last_render;

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
	if (ctx->render && ctx->mode == GAME && get_time() - last_render > ctx->usec_per_frame)
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
	return (0);
}
