/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_buttons.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 17:52:23 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/29 04:29:49 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	reset_game(t_context *ctx)
{
	close_images(ctx);
	free_split(ctx->map.matrix);
	bzero(&ctx->enemies, sizeof(t_enemy));
	ctx->n_enemies = 0;
	bzero(&ctx->explosions, sizeof(t_explosion));
	ctx->n_explosions = 0;
	bzero(&ctx->map.elements, sizeof(t_map_elements));
	ctx->total_enemies = 0;
	ctx->defeated_enemies = 0;
}

void	play_game(t_context *ctx)
{
	mlx_mouse_move(ctx->mlx, ctx->window, ctx->screen.width / 2, ctx->screen.height / 2);
	reset_game(ctx);
	parse_file(ctx, ctx->map_file);
	initialize_minimap(ctx);
	if (ctx->textures.enemy.size)
		convert_transparencies(&ctx->textures.enemy);
	if (ctx->textures.explosion.size)
		convert_transparencies(&ctx->textures.explosion);
	set_textures(ctx);
	// usleep(500000);
	set_velocity(ctx, ctx->config.veloc_lvl.current);
	set_rot_velocity(ctx, ctx->config.rot_veloc_lvl.current);
	set_mouse_sensitivity(ctx, ctx->config.mouse_sens.current);
	limit_fps(ctx, ctx->config.max_fps.current);
	ctx->mode = GAME;
}

void	close_game_success(t_context *ctx)
{
	close_game(ctx, C3D_SUCCESS);
}

void	new_button(t_context *ctx, t_menu_button *button, char *files[2], t_button_action act)
{
	button->image.img = mlx_xpm_file_to_image(
		ctx->mlx, files[0],
		&button->image.width,
		&button->image.height);
	get_img_data(&button->image);
	button->focus_image.img = mlx_xpm_file_to_image(
		ctx->mlx, files[1],
		&button->focus_image.width,
		&button->focus_image.height);
	get_img_data(&button->focus_image);
	convert(&button->image);
	convert(&button->focus_image);
	button->action = act;
}

void	new_config(t_context *ctx, t_config_button *button, char *files[2], t_config_item *conf)
{
	button->image.img = mlx_xpm_file_to_image(
		ctx->mlx, files[0],
		&button->image.width,
		&button->image.height);
	get_img_data(&button->image);
	button->focus_image.img = mlx_xpm_file_to_image(
		ctx->mlx, files[1],
		&button->focus_image.width,
		&button->focus_image.height);
	get_img_data(&button->focus_image);
	convert(&button->image);
	convert(&button->focus_image);
	button->config = conf;
}

void	create_buttons(t_context *ctx)
{
	char *files[2];

	files[0] = "./img/play.xpm";
	files[1] = "./img/play_focus.xpm";
	new_button(ctx, &ctx->buttons[B_PLAY], files, play_game);
	files[0] = "./img/configuration.xpm";
	files[1] = "./img/configuration_focus.xpm";
	new_button(ctx, &ctx->buttons[B_CONFIG], files, open_config);
	files[0] = "./img/exit.xpm";
	files[1] = "./img/exit_focus.xpm";
	new_button(ctx, &ctx->buttons[B_EXIT], files, close_game_success);
	files[0] = "./img/speed.xpm";
	files[1] = "./img/speed_focus.xpm";
	new_config(ctx, &ctx->config_buttons[C_SPEED], files, &ctx->config.veloc_lvl);
	files[0] = "./img/rotation.xpm";
	files[1] = "./img/rotation_focus.xpm";
	new_config(ctx, &ctx->config_buttons[C_ROTATION], files, &ctx->config.rot_veloc_lvl);
	files[0] = "./img/mouse.xpm";
	files[1] = "./img/mouse_focus.xpm";
	new_config(ctx, &ctx->config_buttons[C_MOUSE], files, &ctx->config.mouse_sens);
	files[0] = "./img/map.xpm";
	files[1] = "./img/map_focus.xpm";
	new_config(ctx, &ctx->config_buttons[C_MAP], files, &ctx->config.map_number);
	files[0] = "./img/fps.xpm";
	files[1] = "./img/fps_focus.xpm";
	new_config(ctx, &ctx->config_buttons[C_FPS], files, &ctx->config.max_fps);
	files[0] = "./img/exit.xpm";
	files[1] = "./img/exit_focus.xpm";
	new_config(ctx, &ctx->config_buttons[C_RETURN], files, &ctx->config.max_fps);
}
