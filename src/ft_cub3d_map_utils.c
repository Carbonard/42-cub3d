/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_map_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/03 19:34:44 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/03 23:18:26 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	on_map(t_map *map, t_vector *ray)
{
	if ((int)ray->x >= map->width
		|| (int)ray->y >= map->height
		|| (int)ray->x < 0
		|| (int)ray->y < 0)
		return (0);
	return (1);
}

static int	is_int(double n)
{
	return (n - floor(n) == 0);
}

int	is_wall(t_context *ctx, t_vector *pos)
{
	t_vector	aux;

	if (is_int(pos->x))
	{
		aux.x = pos->x - 0.01;
		aux.y = pos->y;
		if (is_wall(ctx, &aux))
			return (1);
	}
	if (is_int(pos->y))
	{
		aux.x = pos->x;
		aux.y = pos->y - 0.01;
		if (is_wall(ctx, &aux))
			return (1);
	} 
	if (ctx->map.matrix[(int)(pos->y)][(int)(pos->x)] == '1')
		return (1);
	// FOR GOD'S SAKE, REMOVE THIS LINE!!
	if (pos->y <= 1)
		printf("FUCK THIS GUY -> (%lf,%lf)\n", pos->x, pos->y);
	return (0);
}
