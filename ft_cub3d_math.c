/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_math.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 15:07:38 by rselva-2          #+#    #+#             */
/*   Updated: 2026/06/28 21:12:37 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	rotate_vector(t_vector *v, float t_angle)
{
	t_coordinate tmp_x;

	tmp_x = v->x * cos(t_angle) - v->y * sin(t_angle);
	v->y = v->x * sin(t_angle) + v->y * cos(t_angle);
	v->x = tmp_x;
}
