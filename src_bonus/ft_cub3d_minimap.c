/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_minimap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 22:29:51 by rselva-2          #+#    #+#             */
/*   Updated: 2026/08/09 17:46:12 by rselva-2         ###   ########.fr       */
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

static void	put_info_square(t_context *ctx, int x, int y)
{
	int				i;
	int				j;
	int				width;
	int				height;
	unsigned int	color;

	width = 65;
	height = 40;
	color = rgb(200, 200, 200);
	i = 0;
	while (i < width)
	{
		j = 0;
		while (j < height)
		{
			put_pixel(
				&ctx->screen,
				x + i,
				y + j,
				color);
			j++;
		}
		i++;
	}
}

void	render_minimap(t_context *ctx)
{
	char		*aux;

	fill_minimap_player_image(ctx, &ctx->player, ctx->map.minimap_scale);
	merge_images(&ctx->screen, &ctx->map.img, MAP_LEFT_MARGIN, MAP_TOP_MARGIN);
	merge_images(&ctx->screen, &ctx->player.minimap_img,
		MAP_LEFT_MARGIN + (ctx->player.pos.x - 0.5) * ctx->map.minimap_scale,
		MAP_TOP_MARGIN + (ctx->player.pos.y - 0.5) * ctx->map.minimap_scale);
	put_info_square(ctx, ctx->width - 142, ctx->height - 63);
	mlx_put_image_to_window(ctx->mlx, ctx->window, ctx->screen.img, 0, 0);
	aux = ft_itoa(ctx->time / 10);
	mlx_string_put(ctx->mlx, ctx->window, ctx->width - 137, ctx->height - 50,
		rgb(10, 10, 10), "Time: ");
	mlx_string_put(ctx->mlx, ctx->window, ctx->width - 100, ctx->height - 50,
		rgb(10, 10, 10), aux);
	free(aux);
	aux = ft_itoa(ctx->real_fps);
	mlx_string_put(ctx->mlx, ctx->window, ctx->width - 130, ctx->height - 30,
		rgb(10, 10, 100), "FPS: ");
	mlx_string_put(ctx->mlx, ctx->window, ctx->width - 100, ctx->height - 30,
		rgb(10, 10, 100), aux);
	free(aux);
}
