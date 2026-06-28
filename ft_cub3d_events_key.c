/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_events_key.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 14:06:12 by rselva-2          #+#    #+#             */
/*   Updated: 2026/06/28 15:32:07 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	key_press_event(int key, t_context *ctx)
{
	if (key == XK_Escape)
		return (close_window(ctx));
	else if (key == XK_a)
		move_player(ctx, 0, -0.125);
	else if (key == XK_d)
		move_player(ctx, 0, +0.125);
	else if (key == XK_w)
		move_player(ctx, +0.125, 0);
	else if (key == XK_s)
		move_player(ctx, -0.125, 0);
	else if (key == XK_Left)
		rotate_player(ctx, -M_PI * 0.03125);
	else if (key == XK_Right)
		rotate_player(ctx, +M_PI * 0.03125);
	else
		printf("%d, :(\n", key);
	render_minimap(ctx);
	return (0);
}
