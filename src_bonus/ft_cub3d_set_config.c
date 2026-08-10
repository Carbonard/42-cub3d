/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_set_config.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 00:05:49 by rselva-2          #+#    #+#             */
/*   Updated: 2026/08/10 11:35:40 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	limit_fps(t_context *ctx, int max_fps)
{
	ctx->config.max_fps.current = fmin(fmax(max_fps, 1),
			ctx->config.max_fps.max);
	ctx->usec_per_frame = 1000000 / ctx->config.max_fps.current;
}

void	set_velocity(t_context *ctx, int veloc_lvl)
{
	ctx->config.veloc_lvl.current = fmin(fmax(veloc_lvl, 0),
			ctx->config.veloc_lvl.max);
	ctx->player.velocity = (double)1
		/ (ctx->config.veloc_lvl.max - (veloc_lvl) + 1);
}

void	set_rot_velocity(t_context *ctx, int rot_veloc_lvl)
{
	ctx->config.rot_veloc_lvl.current = fmin(fmax(rot_veloc_lvl, 0),
			ctx->config.rot_veloc_lvl.max);
	ctx->player.rot_velocity = M_PI;
	while (rot_veloc_lvl <= ctx->config.rot_veloc_lvl.max)
	{
		ctx->player.rot_velocity *= 0.5;
		rot_veloc_lvl++;
	}
}

void	set_mouse_sensitivity(t_context *ctx, int rot_veloc_lvl)
{
	ctx->config.mouse_sens.current = fmin(fmax(rot_veloc_lvl, 0),
			ctx->config.mouse_sens.max);
	ctx->player.mouse_sensitivity = M_PI / 16;
	while (rot_veloc_lvl <= ctx->config.mouse_sens.max)
	{
		ctx->player.mouse_sensitivity *= 0.5;
		rot_veloc_lvl++;
	}
}

void	set_map_number(t_context *ctx, int n_map)
{
	static char	*maps[MAX_MAPS] = {
		NULL,
		"./maps_bonus/basic.cub",
		"./maps_bonus/subject.cub",
		"./maps_bonus/backrooms.cub",
		"./maps_bonus/rubik.cub",
		"./maps_bonus/spiral.cub",
		"./maps_bonus/warning.cub",
		"./maps_bonus/ELV.cub"
	};

	if (!maps[0])
		maps[0] = ctx->map_file;
	if (n_map < 0)
		n_map += MAX_MAPS;
	if (n_map >= MAX_MAPS)
		n_map %= MAX_MAPS;
	ctx->config.map_number.current = n_map;
	ctx->map_file = maps[n_map];
}
