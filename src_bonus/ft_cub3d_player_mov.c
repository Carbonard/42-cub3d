/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_player_mov.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 14:22:12 by rselva-2          #+#    #+#             */
/*   Updated: 2026/09/07 15:34:00 by rselva-2         ###   ########.fr       */
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

int	check_exit(t_context *ctx, int ret)
{
	char	cell;

	cell = ctx->map.matrix[(int)ctx->player.pos.y][(int)ctx->player.pos.x];
	if (cell == EXIT)
	{
		printf("\n\n\nCONGRATULATIONS!\n\nYou have won in %.2lf seconds!\n\n\n",
			ctx->time / 10);
		ctx->mode = MENU;
		ctx->render = 1;
		return (0);
	}
	if (cell == ENEMY)
	{
		printf("\n\n\nYOU FAILED!\n\nYou have died in %.2lf seconds!\n\n\n",
			ctx->time / 10);
		ctx->mode = MENU;
		ctx->render = 1;
		return (0);
	}
	return (ret);
}

int	move_player(t_context *ctx, t_coordinate forward, t_coordinate side)
{
	t_character	*p;
	t_vector	new_pos;
	int			ret;

	ret = 0;
	p = &ctx->player;
	new_pos.x = p->pos.x
		+ fmax(-1, fmin(1, p->dir.x * forward + p->ort.x * side));
	new_pos.y = ctx->player.pos.y;
	if (!is_wall(&ctx->map, &new_pos))
	{
		p->pos.x = new_pos.x;
		ret = 1;
	}
	else
		new_pos.x = ctx->player.pos.x;
	new_pos.y = p->pos.y
		+ fmax(-1, fmin(1, p->dir.y * forward + p->ort.y * side));
	if (!is_wall(&ctx->map, &new_pos))
	{
		p->pos.y = new_pos.y;
		ret = 1;
	}
	ret = check_exit(ctx, ret);
	return (ret);
}

int	rotate_player(t_context *ctx, double t_angle)
{
	ctx->player.rot_ang += t_angle;
	set_player_vectors(&ctx->player);
	return (1);
}
