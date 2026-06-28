/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 15:13:22 by rselva-2          #+#    #+#             */
/*   Updated: 2026/06/28 15:23:12 by rselva-2         ###   ########.fr       */
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
	ctx->map.size = 250;
	(void) file_name;
	ctx->map.matrix = malloc(11 * sizeof(char *));
	ctx->map.matrix[0] = "1111111111";
	ctx->map.matrix[1] = "1000000001";
	ctx->map.matrix[2] = "1001111101";
	ctx->map.matrix[3] = "1001000001";
	ctx->map.matrix[4] = "1001000001";
	ctx->map.matrix[5] = "1001111001";
	ctx->map.matrix[6] = "1001000001";
	ctx->map.matrix[7] = "1001111101";
	ctx->map.matrix[8] = "1000000001";
	ctx->map.matrix[9] = "1111111111";
	ctx->map.matrix[10] = NULL;
	ctx->map.width = 10;
	ctx->map.height = 10;
	ctx->player.pos.x = 6;
	ctx->player.pos.y = 6;
	ctx->player.rot_ang = -M_PI/2;
	set_player_vectors(&ctx->player);
	return (0);
}

// int	loop_hook(void	*arg)
// {
// 	t_context	*ctx;

// 	ctx = arg;
// 	(void) ctx;
// 	;
// 	return (0);
// }

int	main(int argc, char **argv)
{
	t_context ctx;

	if (!check_args(argc, argv))
		return (1);
	if (set_config(&ctx, argv[1]))
		return (2);

	ctx.mlx = mlx_init();
	if (!ctx.mlx)
		return (3);
	mlx_get_screen_size(ctx.mlx, &ctx.width, &ctx.height);
	printf("%d, %d\n", ctx.width, ctx.height);
	ctx.window = mlx_new_window(ctx.mlx, ctx.width / 2, ctx.height / 2, "cube3D");
	if (!ctx.window)
		return (3);	
	mlx_hook(ctx.window, 17, 0, &close_window, &ctx);
	mlx_hook(ctx.window, KeyPress, KeyPressMask, &key_press_event, &ctx);
	// mlx_loop_hook(ctx.mlx, loop_hook, &ctx);
	initialize_minimap(&ctx);
	render_minimap(&ctx);
	mlx_loop(ctx.mlx);
	mlx_destroy_display(ctx.mlx);
	free(ctx.mlx);
	return (0);
}
