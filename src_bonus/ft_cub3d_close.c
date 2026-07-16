/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_close.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 13:59:21 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/16 18:11:14 by rselva-2         ###   ########.fr       */
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

static void	close_tex_array(void *mlx, t_tex_array *texure)
{
	int	i;

	i = 0;
	while (i < texure->size)
	{
		safe_close_image(mlx, &texure->tex[i].image);
		i++;
	}
	texure->size = 0;
}

void	close_images(t_context *ctx)
{
	safe_close_image(ctx->mlx, &ctx->map.img);
	safe_close_image(ctx->mlx, &ctx->player.minimap_img);
	close_tex_array(ctx->mlx, &ctx->textures.north);
	close_tex_array(ctx->mlx, &ctx->textures.south);
	close_tex_array(ctx->mlx, &ctx->textures.west);
	close_tex_array(ctx->mlx, &ctx->textures.east);
	close_tex_array(ctx->mlx, &ctx->textures.floor);
	close_tex_array(ctx->mlx, &ctx->textures.ceiling);
	close_tex_array(ctx->mlx, &ctx->textures.door);
	close_tex_array(ctx->mlx, &ctx->textures.exit);
	close_tex_array(ctx->mlx, &ctx->textures.enemy);
	close_tex_array(ctx->mlx, &ctx->textures.explosion);
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

int	close_game(t_context *ctx, int exit_code)
{
	int	i;

	print_error(exit_code);
	close_images(ctx);
	safe_close_image(ctx->mlx, &ctx->screen);
	i = 0;
	while (i < B_SIZE)
	{
		safe_close_image(ctx->mlx, &ctx->buttons[i].image);
		safe_close_image(ctx->mlx, &ctx->buttons[i].focus_image);
		i++;
	}
	free_split(ctx->map.matrix);
	if (ctx->mlx && ctx->window)
		mlx_destroy_window(ctx->mlx, ctx->window);
	if (ctx->mlx)
		mlx_destroy_display(ctx->mlx);
	free(ctx->mlx);
	exit (exit_code);
}