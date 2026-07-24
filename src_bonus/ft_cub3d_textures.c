/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/12 02:18:32 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/16 23:56:14 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

static void	set_tex(t_tex_array *texture, int current)
{
	if (texture->size)
		texture->current = &texture->tex[current % texture->size];
}

void	set_textures(t_context *ctx)
{
	set_tex(&ctx->textures.north, ctx->current_tex);
	set_tex(&ctx->textures.south, ctx->current_tex);
	set_tex(&ctx->textures.west, ctx->current_tex);
	set_tex(&ctx->textures.east, ctx->current_tex);
	set_tex(&ctx->textures.floor, ctx->current_tex);
	set_tex(&ctx->textures.ceiling, ctx->current_tex);
	set_tex(&ctx->textures.door, ctx->current_tex);
	set_tex(&ctx->textures.exit, ctx->current_tex);
	set_tex(&ctx->textures.enemy, ctx->current_tex);
}

void	convert(t_mlx_image *image)
{
	int				j;
	int				i;
	unsigned int	color;

	j = 0;
	while (j < image->height)
	{
		i = 0;
		while (i < image->width)
		{
			color = get_pixel(image, i, j);
			if ((color & 0x00FFFFFF) != TRANSPARENT)
				put_pixel(image, i, j, color | 0xFF000000);
			else
				put_pixel(image, i, j, 0);
			i++;
		}
		j++;
	}
}

void	convert_transparencies(t_tex_array *texture)
{
	int	i;

	i = 0;
	while (i < texture->size)
	{
		convert(&texture->tex[i].image);
		i++;
	}
}
