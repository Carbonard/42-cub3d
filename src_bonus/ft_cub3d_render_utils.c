/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_render_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 20:28:43 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/08 15:56:54 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

double	get_step_size(t_ray *ray)
{
	double	x_step;
	double	y_step;

	x_step = ray->h_dist(ray->pos.x);
	y_step = ray->v_dist(ray->pos.y);
	if (x_step < 0.000000001 && y_step < 0.000000001)
		return (1);
	return ((x_step + y_step) / 2);
}

double	upper_dist(double z)
{
	return (ceil(z) - z);
}

double	lower_dist(double z)
{
	return (z - floor(z));
}

// This function is an optimization for:
// v_cos(&player->dir, &ray->dir) * dist(&player->pos, &ray->pos)
double	screen_dist(t_character *player, t_ray *ray)
{
	return ((player->dir.x * ray->dir.x + player->dir.y * ray->dir.y)
			* sqrt((
				((player->pos.x - ray->pos.x)
					* (player->pos.x - ray->pos.x))
				+ ((player->pos.y - ray->pos.y)
					* (player->pos.y - ray->pos.y)))));
}
