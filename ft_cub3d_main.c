/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 15:13:22 by rselva-2          #+#    #+#             */
/*   Updated: 2026/06/27 19:53:32 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	check_args(int argc, char **argv)
{
	size_t	len;

	if (argc != 2)
		return (1);
	len = ft_strlen(argv[1]);
	if (len < 5)
		return (1);
	if (ft_strncmp(argv[1] + len - 4, ".cub", 4))
		return (1);
	return (0);
}

int	set_config(t_context *ctx, char *file_name)
{
	printf("reading file %s\n", file_name);
	ctx->mlx = NULL;
	ctx->window = NULL;
	return (0);
}

int	close_window(void *arg)
{
	t_context	*ctx;

	ctx = arg;
	mlx_destroy_window(ctx->mlx, ctx->window);
	return (0);
}

int	loop_hook(void	*arg)
{
	t_context	*ctx;

	ctx = arg;
	(void) ctx;
	printf("hola\n");
	return (0);
}

int	main(int argc, char **argv)
{
	t_context ctx;

	if (check_args(argc, argv))
		return (1);
	if (set_config(&ctx, argv[1]))
		return (2);
	ctx.mlx = mlx_init();
	mlx_get_screen_size(ctx.mlx, &ctx.width, &ctx.height);
	ctx.window = mlx_new_window(ctx.mlx, ctx.width, ctx.height, "cube3D");
	mlx_hook(ctx.window, 17, 0, &close_window, &ctx);
	mlx_loop_hook(ctx.mlx, loop_hook, &ctx);
	mlx_loop(ctx.mlx);
	mlx_destroy_display(ctx.mlx);
	free(ctx.mlx);
	return (0);
}
