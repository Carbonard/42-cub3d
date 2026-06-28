/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_player_mov.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 14:22:12 by rselva-2          #+#    #+#             */
/*   Updated: 2026/06/28 15:46:50 by rselva-2         ###   ########.fr       */
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

void	move_player(t_context *ctx, coordinate forward, coordinate side)
{
	t_character *p;
	t_vector	new_pos;

	p = &ctx->player;
	new_pos.x = p->pos.x + p->dir.x * forward;
	new_pos.y = p->pos.y + p->dir.y * forward;
	new_pos.x += p->ort.x * side;
	new_pos.y += p->ort.y * side;
	if (ctx->map.matrix[(int)(new_pos.y)][(int)(new_pos.x)] != '1')
	{
		p->pos.x = new_pos.x;
		p->pos.y = new_pos.y;
	}
}

void	rotate_player(t_context *ctx, float angle)
{
	ctx->player.rot_ang += angle;
	set_player_vectors(&ctx->player);
	return ;
	t_character *p;

	p = &ctx->player;
	rotate_vector(&ctx->player.dir, angle);
	p->ort.x = p->dir.x;
	p->ort.y = p->dir.y;
	rotate_vector(&p->ort, M_PI / 2);
}
