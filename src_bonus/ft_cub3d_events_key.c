/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_events_key.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 14:06:12 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/16 18:08:18 by rselva-2         ###   ########.fr       */
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
	else if (key == XK_Up)
		ctx->focus = (ctx->focus + B_SIZE - 1) % B_SIZE;
		// ctx->pressed.up = 1;
	else if (key == XK_Down)
		ctx->focus = (ctx->focus + 1) % B_SIZE;
		// ctx->pressed.down = 1;
	else if (key == XK_space && ctx->mode == GAME)
		open_door(ctx);
	else if (key == XK_space && ctx->mode == MENU)
		ctx->buttons[ctx->focus].action(ctx, 0);
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
	// else if (key == XK_Up)
	// 	ctx->pressed.up = 0;
	// else if (key == XK_Down)
	// 	ctx->pressed.down = 0;
	return (0);
}

static void	set_tex(t_tex_array *texture, int current)
{
	if (texture->size)
		texture->current = &texture->tex[current % texture->size];
}

void	set_textures(t_context *ctx)
{
	set_tex(&ctx->textures.north, ctx->current_tex);
	set_tex(&ctx->textures.south, ctx->current_tex);
	set_tex(&ctx->textures.west, ctx->current_tex);
	set_tex(&ctx->textures.east, ctx->current_tex);
	set_tex(&ctx->textures.floor, ctx->current_tex);
	set_tex(&ctx->textures.ceiling, ctx->current_tex);
	set_tex(&ctx->textures.door, ctx->current_tex);
	set_tex(&ctx->textures.exit, ctx->current_tex);
	set_tex(&ctx->textures.enemy, ctx->current_tex);
}

int	loop_hook(t_context *ctx)
{
	static size_t	last_time;
	static size_t	texture_render_time;
	double			time_increment;
	size_t			current_time;

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
	if (last_time - texture_render_time > 150000)
	{
		texture_render_time = last_time;
		ctx->current_tex++;
		set_textures(ctx);
		ctx->render |= 1;
	}
	if (ctx->render && ctx->mode == GAME)
		render_screen(ctx);
	current_time = get_time();
	if (current_time - last_time < ctx->usec_per_frame)
		usleep(ctx->usec_per_frame - (current_time - last_time));
	return (0);
}
