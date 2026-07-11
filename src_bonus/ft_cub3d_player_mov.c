/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_player_mov.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elangari <elangari@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 14:22:12 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/11 19:40:05 by elangari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	set_player_vectors(t_character *player)
{
	player->dir.x = cos(player->rot_ang);
	player->dir.y = sin(player->rot_ang);
	player->ort.x = cos(player->rot_ang + M_PI / 2);
	player->ort.y = sin(player->rot_ang + M_PI / 2);
}

int	move_player(t_context *ctx, t_coordinate forward, t_coordinate side)
{
	t_character	*p;
	t_vector	new_pos;
	int			ret;

	ret = 0;
	p = &ctx->player;
	new_pos.x = p->pos.x + p->dir.x * forward + p->ort.x * side;
	new_pos.y = ctx->player.pos.y;
	if (!is_wall(&ctx->map, &new_pos))
	{
		p->pos.x = new_pos.x;
		ret = 1;
	}
	else
		new_pos.x = ctx->player.pos.x;
	new_pos.y = p->pos.y + p->dir.y * forward + p->ort.y * side;
	if (!is_wall(&ctx->map, &new_pos))
	{
		p->pos.y = new_pos.y;
		ret = 1;
	}
	return (ret);
}

int	rotate_player(t_context *ctx, float t_angle)
{
	ctx->player.rot_ang += t_angle;
	set_player_vectors(&ctx->player);
	return (1);
}
