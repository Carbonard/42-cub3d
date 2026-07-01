/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_math.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 15:07:38 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/01 14:18:28 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	rotate_vector(t_vector *v, t_angle t_angle)
{
	t_coordinate tmp_x;

	tmp_x = v->x * cos(t_angle) - v->y * sin(t_angle);
	v->y = v->x * sin(t_angle) + v->y * cos(t_angle);
	v->x = tmp_x;
}

void	normalize_vector(t_vector *v)
{
	float	m;

	m = sqrt(v->x * v->x + v->y * v->y);
	v->x *= m;
	v->y *= m;
}

double dist(t_vector *u, t_vector *v)
{
	// return (fabs(u->x - v->x));
	return (sqrt((u->x - v->x) * (u->x - v->x)
		+ (u->y - v->y) * (u->y - v->y)));
}
