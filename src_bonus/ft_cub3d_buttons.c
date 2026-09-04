/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_buttons.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 17:52:23 by rselva-2          #+#    #+#             */
/*   Updated: 2026/09/04 08:44:15 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	new_button(t_context *ctx, t_menu_button *button, char *files[2],
			t_button_action act)
{
	read_xpm(ctx, &button->image, files[0]);
	read_xpm(ctx, &button->focus_image, files[1]);
	// button->image.img = mlx_xpm_file_to_image(
	// 		ctx->mlx, files[0],
	// 		&button->image.width,
	// 		&button->image.height);
	// get_img_data(&button->image);
	// button->focus_image.img = mlx_xpm_file_to_image(
	// 		ctx->mlx, files[1],
	// 		&button->focus_image.width,
	// 		&button->focus_image.height);
	// get_img_data(&button->focus_image);
	convert(&button->image);
	convert(&button->focus_image);
	button->action = act;
}

void	new_config(t_context *ctx, t_config_button *button, char *files[2],
			t_config_item *conf)
{
	read_xpm(ctx, &button->image[0], files[0]);
	read_xpm(ctx, &button->image[1], files[1]);
	// button->image[0].img = mlx_xpm_file_to_image(
	// 		ctx->mlx, files[0],
	// 		&button->image[0].width,
	// 		&button->image[0].height);
	// get_img_data(&button->image[0]);
	// button->image[1].img = mlx_xpm_file_to_image(
	// 		ctx->mlx, files[1],
	// 		&button->image[1].width,
	// 		&button->image[1].height);
	// get_img_data(&button->image[1]);
	convert(&button->image[0]);
	convert(&button->image[1]);
	button->config = conf;
}

static void	create_config_buttons(t_context *ctx, char *files[2])
{
	files[0] = "./img/speed.xpm";
	files[1] = "./img/speed_focus.xpm";
	new_config(ctx, &ctx->config_buttons[C_SPEED], files,
		&ctx->config.veloc_lvl);
	files[0] = "./img/rotation.xpm";
	files[1] = "./img/rotation_focus.xpm";
	new_config(ctx, &ctx->config_buttons[C_ROTATION], files,
		&ctx->config.rot_veloc_lvl);
	files[0] = "./img/mouse.xpm";
	files[1] = "./img/mouse_focus.xpm";
	new_config(ctx, &ctx->config_buttons[C_MOUSE], files,
		&ctx->config.mouse_sens);
	files[0] = "./img/map.xpm";
	files[1] = "./img/map_focus.xpm";
	new_config(ctx, &ctx->config_buttons[C_MAP], files,
		&ctx->config.map_number);
	files[0] = "./img/fps.xpm";
	files[1] = "./img/fps_focus.xpm";
	new_config(ctx, &ctx->config_buttons[C_FPS], files,
		&ctx->config.max_fps);
	files[0] = "./img/exit.xpm";
	files[1] = "./img/exit_focus.xpm";
	new_config(ctx, &ctx->config_buttons[C_RETURN], files,
		&ctx->config.max_fps);
}

void	create_buttons(t_context *ctx)
{
	char	*files[2];

	files[0] = "./img/play.xpm";
	files[1] = "./img/play_focus.xpm";
	new_button(ctx, &ctx->buttons[B_PLAY], files, play_game);
	files[0] = "./img/configuration.xpm";
	files[1] = "./img/configuration_focus.xpm";
	new_button(ctx, &ctx->buttons[B_CONFIG], files, open_config);
	files[0] = "./img/exit.xpm";
	files[1] = "./img/exit_focus.xpm";
	new_button(ctx, &ctx->buttons[B_EXIT], files, close_game_success);
	create_config_buttons(ctx, files);
}
