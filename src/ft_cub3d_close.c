/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_close.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 13:59:21 by rselva-2          #+#    #+#             */
/*   Updated: 2026/06/29 15:51:13 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	close_images(t_context *ctx)
{
	if (ctx->map.img.img)
	{
		mlx_destroy_image(ctx->mlx, ctx->map.img.img);
		ctx->map.img.img = NULL;
	}
	if (ctx->player.minimap_img.img)
	{
		mlx_destroy_image(ctx->mlx, ctx->player.minimap_img.img);
		ctx->player.minimap_img.img = NULL;
	}
}

void	close_textures(void *mlx, t_textures *textures)
{
	if (textures->north.img)
	{
		mlx_destroy_image(mlx, textures->north.img);
		textures->north.img = NULL;
	}
	if (textures->south.img)
	{
		mlx_destroy_image(mlx, textures->south.img);
		textures->south.img = NULL;
	}
	if (textures->west.img)
	{
		mlx_destroy_image(mlx, textures->west.img);
		textures->west.img = NULL;
	}
	if (textures->east.img)
	{
		mlx_destroy_image(mlx, textures->east.img);
		textures->east.img = NULL;
	}
}

void	print_error(int exit_code)
{
	if (exit_code == C3D_MALLOC)
		write(2, "Malloc failed\n", 14);
	if (exit_code == C3D_BAD_FILE)
		write(2, "Wrong file\n", 11);
	if (exit_code == C3D_FILE_PARSER_ERROR)
		write(2, "Wrong file content format\n", 26);
	if (exit_code == C3D_MAP_PARSER)
		write(2, "Wrong character in map\n", 23);
	if (exit_code == C3D_OPEN_MAP)
		write(2, "The map is not closed\n", 22);
}

int	close_game(void *arg, int exit_code)
{
	t_context	*ctx;

	ctx = arg;
	print_error(exit_code);
	close_images(ctx);
	close_textures(ctx->mlx, &ctx->textures);
	free_split(ctx->map.matrix);
	if (ctx->mlx && ctx->window)
		mlx_destroy_window(ctx->mlx, ctx->window);
	if (ctx->mlx)
		mlx_destroy_display(ctx->mlx);
	free(ctx->mlx);
	exit (exit_code);
}
