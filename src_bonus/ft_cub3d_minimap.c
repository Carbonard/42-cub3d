/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_minimap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 22:29:51 by rselva-2          #+#    #+#             */
/*   Updated: 2026/09/10 20:11:28 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

static int	is_player(t_coordinate x, t_coordinate y, int size, t_angle rot)
{
	t_vector	tmp;

	tmp.x = x - size / 2;
	tmp.y = y - size / 2;
	rotate_vector(&tmp, -M_PI / 2 - rot);
	x = tmp.x + size / 2;
	y = tmp.y + size / 2;
	if (x > size / 2)
	{
		if ((x - size / 2) / (size / 2) * size < y
			&& y < size * 2 / 3 + (x - size / 2) / (size / 2) * size / 3)
			return (1);
	}
	else if ((size / 2 - x) / (size / 2) * size < y
		&& y < size * 2 / 3 + (size / 2 - x) / (size / 2) * size / 3)
		return (1);
	return (0);
}

static void	fill_minimap_player_image(t_context *ctx,
			t_character *player, t_coordinate size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (is_player(i, j, size, player->rot_ang))
				put_pixel(&player->minimap_img, i, j,
					ctx->map.minimap_player_color);
			else
				put_pixel(&player->minimap_img, i, j, 0);
			j++;
		}
		i++;
	}
}

void	merge_images(t_mlx_image *main, t_mlx_image *other, int x, int y)
{
	int	i;
	int	j;

	j = 0;
	while (j < other->height)
	{
		i = 0;
		while (i < other->width)
		{
			put_pixel(main, x + i, y + j,
				merge_colors(
					get_pixel(main, x + i, y + j),
					get_pixel(other, i, j)));
			i++;
		}
		j++;
	}
}

void	render_minimap(t_context *ctx)
{
	fill_minimap_player_image(ctx, &ctx->player, ctx->map.minimap_scale);
	merge_images(&ctx->screen, &ctx->map.img, MAP_LEFT_MARGIN, MAP_TOP_MARGIN);
	merge_images(&ctx->screen, &ctx->player.minimap_img,
		MAP_LEFT_MARGIN + (ctx->player.pos.x - 0.5) * ctx->map.minimap_scale,
		MAP_TOP_MARGIN + (ctx->player.pos.y - 0.5) * ctx->map.minimap_scale);
}
