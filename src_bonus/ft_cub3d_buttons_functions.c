/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_buttons_functions.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 11:23:00 by rselva-2          #+#    #+#             */
/*   Updated: 2026/08/10 11:30:00 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	reset_game(t_context *ctx)
{
	close_images(ctx);
	free_split(ctx->map.matrix);
	bzero(&ctx->enemies, sizeof(t_enemy));
	ctx->n_enemies = 0;
	bzero(&ctx->explosions, sizeof(t_explosion));
	ctx->n_explosions = 0;
	bzero(&ctx->map.elements, sizeof(t_map_elements));
	ctx->total_enemies = 0;
	ctx->defeated_enemies = 0;
}

void	play_game(t_context *ctx)
{
	mlx_mouse_move(ctx->mlx, ctx->window,
		ctx->screen.width / 2, ctx->screen.height / 2);
	reset_game(ctx);
	parse_file(ctx, ctx->map_file);
	initialize_minimap(ctx);
	if (ctx->textures.enemy.size)
		convert_transparencies(&ctx->textures.enemy);
	if (ctx->textures.explosion.size)
		convert_transparencies(&ctx->textures.explosion);
	set_textures(ctx);
	set_velocity(ctx, ctx->config.veloc_lvl.current);
	set_rot_velocity(ctx, ctx->config.rot_veloc_lvl.current);
	set_mouse_sensitivity(ctx, ctx->config.mouse_sens.current);
	limit_fps(ctx, ctx->config.max_fps.current);
	ctx->time = 0;
	ctx->mode = GAME;
}

void	close_game_success(t_context *ctx)
{
	close_game(ctx, C3D_SUCCESS);
}
