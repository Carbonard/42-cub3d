/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 15:13:22 by rselva-2          #+#    #+#             */
/*   Updated: 2026/09/11 22:59:30 by rselva-2         ###   ########.fr       */
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

void	set_config(t_context *ctx)
{
	ctx->config.max_fps.max = MAX_FPS;
	ctx->config.max_fps.current = DEF_FPS;
	ctx->config.max_fps.setter = limit_fps;
	ctx->config.veloc_lvl.max = MAX_MOV_VELOC;
	ctx->config.veloc_lvl.current = DEF_MOV_VELOC;
	ctx->config.veloc_lvl.setter = set_velocity;
	ctx->config.rot_veloc_lvl.max = MAX_ROT_VELOC;
	ctx->config.rot_veloc_lvl.current = DEF_ROT_VELOC;
	ctx->config.rot_veloc_lvl.setter = set_rot_velocity;
	ctx->config.mouse_sens.max = 10;
	ctx->config.mouse_sens.current = 5;
	ctx->config.mouse_sens.setter = set_mouse_sensitivity;
	ctx->config.map_number.max = MAX_MAPS - 1;
	ctx->config.map_number.current = 0;
	ctx->config.map_number.setter = set_map_number;
}

int	init_values(t_context *ctx, char *file_name)
{
	ft_bzero(ctx, sizeof(t_context));
	ctx->mlx = mlx_init();
	if (!ctx->mlx)
		exit (C3D_MLX);
	ctx->map_file = file_name;
	ctx->map.minimap_wall_color = argb(200, 0, 0, 0);
	ctx->map.minimap_floor_color = argb(50, 255, 255, 255);
	ctx->map.minimap_player_color = argb(200, 20, 20, 200);
	ctx->map.minimap_enemy_color = argb(200, 200, 20, 20);
	ctx->map.minimap_exit_color = argb(200, 20, 20, 200);
	read_xpm(ctx, &ctx->textures.title, "./img/title.xpm");
	convert(&ctx->textures.title);
	read_xpm(ctx, &ctx->textures.arm, "./img/dw_arm.xpm");
	convert(&ctx->textures.arm);
	create_buttons(ctx);
	set_config(ctx);
	return (0);
}

int	init_window_config(t_context *ctx)
{
	mlx_get_screen_size(ctx->mlx, &ctx->width, &ctx->height);
	ctx->height *= (float)19 / 20;
	ctx->window = mlx_new_window(ctx->mlx, ctx->width, ctx->height, "cube3D");
	if (!ctx->window)
		return (C3D_MLX);
	ctx->pix_size = ctx->height / 1850 + 1;
	ctx->width /= ctx->pix_size;
	ctx->height /= ctx->pix_size;
	activate_mouse(ctx, 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_context	ctx;

	if (check_args(argc, argv))
		return (-1);
	init_values(&ctx, argv[1]);
	if (init_window_config(&ctx))
		return (C3D_MLX);
	mlx_hook(ctx.window, 17, 0, &close_game, &ctx);
	mlx_hook(ctx.window, KeyPress, KeyPressMask, &key_press_event, &ctx);
	mlx_hook(ctx.window, KeyRelease, KeyReleaseMask, &key_release_event, &ctx);
	mlx_loop_hook(ctx.mlx, loop_hook, &ctx);
	initialize_screen(&ctx);
	ctx.mode = MENU;
	ctx.render = 1;
	mlx_loop(ctx.mlx);
	mlx_destroy_display(ctx.mlx);
	free(ctx.mlx);
	return (0);
}
