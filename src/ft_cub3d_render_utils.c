/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_render_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 20:28:43 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/08 21:33:46 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

double	get_step_size(t_ray *ray)
{
	double	x_step;
	double	y_step;

	x_step = ray->h_dist(ray->pos.x);
	y_step = ray->v_dist(ray->pos.y);
	if ((x_step < 0.00000000001 && y_step < 0.00000000001))
		return (1);
	return ((x_step + y_step) * 0.5);
}

double	upper_dist(double z)
{
	if ((ceil(z) - z) == 0)
		return (1);
	return (ceil(z) - z);
}

double	lower_dist(double z)
{
	if ((z - floor(z)) == 0)
		return (1);
	return (z - floor(z));
}
