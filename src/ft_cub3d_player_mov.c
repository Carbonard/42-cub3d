/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_player_mov.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 14:22:12 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/03 22:55:06 by rselva-2         ###   ########.fr       */
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
	t_character *p;
	t_vector	new_pos;

	p = &ctx->player;
	new_pos.x = p->pos.x + p->dir.x * forward;
	new_pos.y = p->pos.y + p->dir.y * forward;
	new_pos.x += p->ort.x * side;
	new_pos.y += p->ort.y * side;
	if (!is_wall(ctx, &new_pos))
	{
		p->pos.x = new_pos.x;
		p->pos.y = new_pos.y;
		return (1);
	}
	return (0);
}

int	rotate_player(t_context *ctx, float t_angle)
{
	ctx->player.rot_ang += t_angle;
	set_player_vectors(&ctx->player);
	return (1);
}
