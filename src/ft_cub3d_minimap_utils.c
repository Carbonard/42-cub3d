/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_minimap_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 20:26:07 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/04 20:26:16 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	display_minimap_point(t_map *map, t_coordinate x, t_coordinate y, unsigned int color, int size)
{
	int a = size;
	for (int i = -a; i < a; i++)
		for (int j = -a; j < a; j++)
			put_pixel(&map->img, (int)(x  * map->scale + i), (int)(y * map->scale + j), color);
}

void	display_miniray(t_context *ctx, t_mobile_vector *ray, unsigned int color)
{
	t_vector	p;
	double		i;

	i = 0;
	while (i < 1)
	{
		p.x = ctx->player.pos.x + i * (ray->pos.x - ctx->player.pos.x);
		p.y = ctx->player.pos.y + i * (ray->pos.y - ctx->player.pos.y);
		display_minimap_point(&ctx->map, p.x, p.y, color, 2);
		i += 0.01;
	}
	put_pixel(&ctx->map.img, (int)(p.x * ctx->map.scale), (int)(p.y * ctx->map.scale), rgb(255,0,0));
}
