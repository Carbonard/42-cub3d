/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_load_config.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 18:47:56 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/07 17:37:36 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

static int	load_image(t_context *ctx, char *file_name, t_mlx_image *img)
{
	size_t	len;

	while (*file_name == ' ')
		file_name++;
	len = ft_strlen(file_name);
	if (file_name[len - 1] == '\n')
		file_name[len - 1] = 0;
	printf("%p, %p\n", ctx->mlx, img->img);
	img->img = mlx_xpm_file_to_image(
			ctx->mlx, file_name, &img->width, &img->height);
	if (!img->img)
	{
		ft_putstr_fd("Error\n", 2);
		perror(file_name);
		return (C3D_BAD_TEX_FILE);
	}
	get_img_data(img);
	return (C3D_SUCCESS);
}

static int	set_color(char *str, t_texture *texture)
{
	int	color[3];
	int	cnt;

	cnt = 0;
	while (*str == ' ')
		str++;
	while (*str && cnt <= 2)
	{
		color[cnt] = atoi(str);
		while (ft_isdigit(*str))
			str++;
		if ((color[cnt] < 0 || color[cnt] > 255) || (*str != ',' && cnt != 2))
			return (C3D_BAD_COLOR);
		if (cnt != 2)
			str++;
		cnt++;
	}
	while (*str == ' ')
		str++;
	if (*str != '\n')
		return (C3D_BAD_COLOR);
	texture->color = rgb(color[0], color[1], color[2]);
	return (C3D_SUCCESS);
}

static t_texture	*get_texture(t_context *ctx, char *line)
{
	int	i;
	const t_str_to_tex	textures[] = {
		{.str = "NO ", .texture = &ctx->textures.north},
		{.str = "SO ", .texture = &ctx->textures.south},
		{.str = "WE ", .texture = &ctx->textures.west},
		{.str = "EA ", .texture = &ctx->textures.east},
		{.str = "F ", .texture = &ctx->textures.floor},
		{.str = "C ", .texture = &ctx->textures.ceiling},
		{.str = NULL, .texture = NULL}
	};

	i = 0;
	while (textures[i].str)
	{
		if (!ft_strncmp(line, textures[i].str, ft_strlen(textures[i].str)))
			return (textures[i].texture);
		i++;
	}
	return (NULL);
}

int	load_texture(t_context *ctx, char *line)
{
	t_texture	*texture;

	texture = get_texture(ctx, line);
	if (!texture)
		return (C3D_NO_TEXTURE);
	while (*line != ' ')
		line++;
	printf("%p\n", texture->image.img);
	if ((set_color(line, texture) == C3D_SUCCESS)
		|| (load_image(ctx, line, &texture->image) == C3D_SUCCESS))
	{
		texture->set = 1;
		return (C3D_SUCCESS);
	}
	return (C3D_FILE_PARSER_ERROR);
}
