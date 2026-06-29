/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_minimap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 22:29:51 by rselva-2          #+#    #+#             */
/*   Updated: 2026/06/28 21:12:37 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

static int	is_player(t_coordinate x, t_coordinate y, int scale, t_angle rot)
{
	t_vector	tmp;

	tmp.x = x - scale / 2;
	tmp.y = y - scale / 2;
	rotate_vector(&tmp, -M_PI / 2 - rot);
	x = tmp.x + scale / 2;
	y = tmp.y + scale / 2;
	if (x > scale / 2)
	{
		if ((x - scale / 2) / (scale / 2) * scale < y
			&& y < scale * 2/3 + (x - scale / 2) / (scale / 2) * scale / 3)
			return (1);
	}
	else if ((scale / 2 - x) / (scale / 2) * scale < y
			&& y < scale * 2/3 + (scale / 2 - x) / (scale / 2) * scale / 3)
			return (1);
	return (0);
}

static void	fill_minimap_player_image(t_character *player, t_coordinate scale)
{
	int	i;
	int	j;

	i = 0;
	while (i < scale)
	{
		j = 0;
		while (j < scale)
		{
			if (is_player(i, j, scale, player->rot_ang))
			{
				put_pixel(&player->minimap_img, i, j, rgb(0,0,255));
			}
			else
				put_pixel(&player->minimap_img, i, j, rgb(255,255,255));
			j++;
		}
		i++;
	}
}

void	render_minimap(t_context *ctx)
{
	t_mlx_image	*player_img;
	int			x;
	int			y;

	player_img = &ctx->player.minimap_img;
	x = 20;
	y = 20;
	if (player_img->img)
		mlx_destroy_image(ctx->mlx, player_img->img);
	player_img->width = ctx->map.scale;
	player_img->height = ctx->map.scale;
	player_img->img = mlx_new_image(ctx->mlx, ctx->map.scale, ctx->map.scale);
	get_img_data(player_img);
	fill_minimap_player_image(&ctx->player, ctx->map.scale);
	mlx_put_image_to_window(ctx->mlx, ctx->window, ctx->map.img.img, x, y);
	mlx_put_image_to_window(ctx->mlx, ctx->window,
		ctx->player.minimap_img.img, x + ctx->player.pos.x * ctx->map.scale,
		y + ctx->player.pos.y * ctx->map.scale);
}
