/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 15:13:22 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/05 21:10:15 by rselva-2         ###   ########.fr       */
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
	ft_bzero(ctx, sizeof(t_context));
	ctx->mlx = mlx_init();
	printf("mlx: %p\n", ctx->mlx);
	if (!ctx->mlx)
		exit (2);
	read_file(ctx, file_name);
	ctx->textures.c_north = rgb(42, 42, 42);
	ctx->textures.c_west = rgb(84, 84, 84);
	// ctx->textures.floor = rgb(0, 42, 21);
	// ctx->textures.ceil = rgb(0, 0, 50);
	// 								rgb(50, 0, 155)
	ctx->map.minimap_wall_color = argb(230, 0, 0, 0);
	ctx->map.minimap_floor_color = argb(50, 255, 255, 255);
	ctx->map.minimap_player_color = argb(200, 200, 20, 20);
	ctx->player.velocity = 0.33;
	ctx->player.ang_velocity = M_PI * 0.0625;
	return (0);
}

int	main(int argc, char **argv)
{
	t_context ctx;

	if (check_args(argc, argv))
		return (1);
	set_config(&ctx, argv[1]);
	mlx_get_screen_size(ctx.mlx, &ctx.width, &ctx.height);
	// ctx.width = 1000;
	// ctx.height = 500;
	ctx.window = mlx_new_window(ctx.mlx, ctx.width, ctx.height, "cube3D");
	if (!ctx.window)
		return (3);	
	mlx_hook(ctx.window, 17, 0, &close_game, &ctx);
	mlx_hook(ctx.window, KeyPress, KeyPressMask, &key_press_event, &ctx);
	mlx_hook(ctx.window, KeyRelease, KeyReleaseMask, &key_release_event, &ctx);
	mlx_loop_hook(ctx.mlx, loop_hook, &ctx);
	initialize_minimap(&ctx);
	render_screen(&ctx);
	mlx_loop(ctx.mlx);
	mlx_destroy_display(ctx.mlx);
	free(ctx.mlx);
	return (0);
}
