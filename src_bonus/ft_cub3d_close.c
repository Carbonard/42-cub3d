/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_close.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 13:59:21 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/07 19:43:03 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

static void	safe_close_image(void *mlx, t_mlx_image *image)
{
	if (image->img)
	{
		mlx_destroy_image(mlx, image->img);
		image->img = NULL;
	}
}

static void	close_images(t_context *ctx)
{
	safe_close_image(ctx->mlx, &ctx->map.img);
	safe_close_image(ctx->mlx, &ctx->player.minimap_img);
	safe_close_image(ctx->mlx, &ctx->screen);
	int i = 0;
	while (i < 5)
	{
		safe_close_image(ctx->mlx, &ctx->textures.north.tex[i].image);
		safe_close_image(ctx->mlx, &ctx->textures.south.tex[i].image);
		safe_close_image(ctx->mlx, &ctx->textures.west.tex[i].image);
		safe_close_image(ctx->mlx, &ctx->textures.east.tex[i].image);
		safe_close_image(ctx->mlx, &ctx->textures.floor.tex[i].image);
		safe_close_image(ctx->mlx, &ctx->textures.ceiling.tex[i].image);
		i++;
	}
}

static void	print_error(int exit_code)
{
	if (exit_code == C3D_MALLOC)
		ft_putendl_fd("Malloc failed", 2);
	if (exit_code == C3D_BAD_FILE)
		ft_putendl_fd("Wrong file", 2);
	if (exit_code == C3D_FILE_PARSER_ERROR)
		ft_putendl_fd("Wrong file content format", 2);
	if (exit_code == C3D_MAP_PARSER)
		ft_putendl_fd("Wrong character in map", 2);
	if (exit_code == C3D_OPEN_MAP)
		ft_putendl_fd("The map is not closed", 2);
}

int	close_game(void *arg, int exit_code)
{
	t_context	*ctx;

	ctx = arg;
	print_error(exit_code);
	close_images(ctx);
	free_split(ctx->map.matrix);
	if (ctx->mlx && ctx->window)
		mlx_destroy_window(ctx->mlx, ctx->window);
	if (ctx->mlx)
		mlx_destroy_display(ctx->mlx);
	free(ctx->mlx);
	exit (exit_code);
}
