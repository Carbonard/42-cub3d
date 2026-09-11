/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_minimap_init.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 13:41:24 by rselva-2          #+#    #+#             */
/*   Updated: 2026/09/10 16:59:41 by rselva-2         ###   ########.fr       */
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
			if (map->matrix[j][i] == WALL
				|| map->matrix[j][i] == CLOSED_DOOR)
				put_square(map, i, j, map->minimap_wall_color);
			else if (map->matrix[j][i] == FLOOR
				|| map->matrix[j][i] == OPEN_DOOR)
				put_square(map, i, j, map->minimap_floor_color);
			else if (map->matrix[j][i] == ENEMY
				|| map->matrix[j][i] == EXPLOSION)
				put_square(map, i, j, map->minimap_enemy_color);
			else if (map->matrix[j][i] == EXIT)
				put_square(map, i, j, map->minimap_exit_color);
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

void	initialize_minimap(t_context *ctx)
{
	ctx->map.minimap_scale = max((double)ctx->width * 0.3 / ctx->map.width, 3);
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

void	initialize_screen(t_context *ctx)
{
	ctx->screen.width = ctx->width;
	ctx->screen.height = ctx->height;
	ctx->screen.img = mlx_new_image(ctx->mlx, ctx->width, ctx->height);
	get_img_data(&ctx->screen);
	ctx->real_screen.width = ctx->width * ctx->pix_size;
	ctx->real_screen.height = ctx->height * ctx->pix_size;
	ctx->real_screen.img = mlx_new_image(ctx->mlx, ctx->width * ctx->pix_size, ctx->height * ctx->pix_size);
	get_img_data(&ctx->real_screen);
}
