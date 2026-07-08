/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_minimap_init.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 13:41:24 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/08 19:41:43 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

static void	put_square(t_map *map, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->minimap_scale)
	{
		j = 0;
		while (j < map->minimap_scale)
		{
			put_pixel(
				&map->img,
				x * map->minimap_scale + i,
				y * map->minimap_scale + j,
				color);
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
				put_square(map, i, j, map->minimap_wall_color);
			else if (map->matrix[j][i] == '0')
				put_square(map, i, j, map->minimap_floor_color);
			else
				put_square(map, i, j, rgb(255, 0, 0));
			i++;
		}
		j++;
	}
}

int	max(int a, int b)
{
	if (a < b)
		return (b);
	else
		return (a);
}

void	initialize_screen(t_context *ctx)
{
	ctx->screen.width = ctx->width;
	ctx->screen.height = ctx->height;
	ctx->screen.img = mlx_new_image(ctx->mlx, ctx->width, ctx->height);
	get_img_data(&ctx->screen);
	ctx->map.size = ctx->width * 0.3;
	ctx->map.minimap_scale = max((double)ctx->map.size / ctx->map.width, 3);
	ctx->map.img.width = ctx->map.width * ctx->map.minimap_scale;
	ctx->map.img.height = ctx->map.height * ctx->map.minimap_scale;
	ctx->map.img.img = mlx_new_image(
			ctx->mlx,
			ctx->map.img.width,
			ctx->map.img.height);
	get_img_data(&ctx->map.img);
	ctx->player.minimap_img.width = ctx->map.minimap_scale;
	ctx->player.minimap_img.height = ctx->map.minimap_scale;
	ctx->player.minimap_img.img = mlx_new_image(
			ctx->mlx, ctx->map.minimap_scale, ctx->map.minimap_scale);
	get_img_data(&ctx->player.minimap_img);
	fill_minimap_image(&ctx->map);
}
