/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_events_key.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 14:06:12 by rselva-2          #+#    #+#             */
/*   Updated: 2026/09/11 23:03:39 by rselva-2         ###   ########.fr       */
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
		if (DEBUG)
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
		ctx->config_buttons[ctx->config_focus].config->setter(ctx,
			ctx->config_buttons[ctx->config_focus].config->current - 1);
	else if (key == XK_Right)
		ctx->config_buttons[ctx->config_focus].config->setter(ctx,
			ctx->config_buttons[ctx->config_focus].config->current + 1);
	else
	{
		if (DEBUG)
			printf("Invalid key: %d\n", key);
		return ;
	}
	ctx->render = 1;
}

static int	key_press_menu(int key, t_context *ctx)
{
	if (key == XK_p)
	{
		ctx->mode = MENU;
		ctx->render = 1;
	}
	else if (ctx->mode == MENU)
		menu_key_events(ctx, key);
	else if (ctx->mode == CONFIG)
		config_key_events(ctx, key);
	else
		return (0);
	return (1);
}

int	key_press_event(int key, t_context *ctx)
{
	if (key == XK_Escape)
		return (close_game(ctx, 0));
	if (key_press_menu(key, ctx))
		return (0);
	else if (key == XK_m)
		activate_mouse(ctx, !ctx->mouse_active);
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
	else if (DEBUG)
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
