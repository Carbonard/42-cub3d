/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_minimap_init.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 13:41:24 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/03 19:05:50 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

static void	put_square(t_map *map, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->scale)
	{
		j = 0;
		while (j < map->scale)
		{
			if (i == 0 || j == 0)
				put_pixel(&map->img, x * map->scale + i, y * map->scale + j, rgb(0,100,100));
			else
				put_pixel(&map->img, x * map->scale + i, y * map->scale + j, color);
			j++;
		}
		i++;
	}
}

void	fill_minimap_image(t_map *map)
{
	int	i;
	int	j;

	j = 0;
	while (map->matrix[j])
	{
		i = 0;
		while (map->matrix[j][i])
		{
			if (map->matrix[j][i] == '1')
				put_square(map, i, j, rgb(150, 50, 255));
			else if (map->matrix[j][i] == '0')
				put_square(map, i, j, rgb(255, 255, 255));
			else
				put_square(map, i, j, rgb(255, 0, 0));
			i++;
		}
		j++;
	}
}

void	initialize_minimap(t_context *ctx)
{
	ctx->map.size = ctx->width * 0.2;
	ctx->map.scale = ctx->map.size / ctx->map.width;
	ctx->map.img.width = ctx->map.size;
	ctx->map.img.height = ctx->map.size * ctx->map.height / ctx->map.width;
	printf("width: %d\nheight: %d\nscale: %d\n", ctx->map.img.width, ctx->map.img.height, ctx->map.scale);
	if (!ctx->map.img.img)
	{
		ctx->map.img.img = mlx_new_image(ctx->mlx,
			ctx->map.img.width + ctx->map.scale,
			ctx->map.img.height + ctx->map.scale);
		get_img_data(&ctx->map.img);
	}
	fill_minimap_image(&ctx->map);
}
