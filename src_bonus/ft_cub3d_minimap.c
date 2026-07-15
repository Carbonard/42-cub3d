/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_minimap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 22:29:51 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/15 20:36:34 by rselva-2         ###   ########.fr       */
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

void	fill_minimap_player_image(t_context *ctx,
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

// This function just considers the c2 color transparency
unsigned int	merge_colors(unsigned int c1, unsigned int c2)
{
	double	a;

	a = (double)(c2 >> 24) / 0xFF;
	return (((unsigned int)((1 - a) * (c1 & RED) + a * (c2 & RED)) & RED)
		+ ((unsigned int)((1 - a) * (c1 & GREEN) + a * (c2 & GREEN)) & GREEN)
		+ ((unsigned int)((1 - a) * (c1 & BLUE) + a * (c2 & BLUE)) & BLUE));
}

void	merge_images(t_mlx_image *main, t_mlx_image *other, int x, int y)
{
	int				i;
	int				j;

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
	int			x_margin;
	int			y_margin;

	x_margin = 10;
	y_margin = 10;
	fill_minimap_player_image(ctx, &ctx->player, ctx->map.minimap_scale);
	merge_images(&ctx->screen, &ctx->map.img, x_margin, y_margin);
	merge_images(&ctx->screen, &ctx->player.minimap_img,
		x_margin + (ctx->player.pos.x - 0.5) * ctx->map.minimap_scale,
		y_margin + (ctx->player.pos.y - 0.5) * ctx->map.minimap_scale);
	mlx_put_image_to_window(ctx->mlx, ctx->window, ctx->screen.img, 0, 0);
	char *time = ft_itoa(ctx->time / 10);
	mlx_string_put(ctx->mlx, ctx->window, ctx->width - 100, ctx->height - 50, rgb(10, 10, 100), time);
	char *fps = ft_itoa(ctx->fps);
	mlx_string_put(ctx->mlx, ctx->window, ctx->width - 100, ctx->height - 30, rgb(10, 10, 100), fps);
	free(time);
	free(fps);
}
