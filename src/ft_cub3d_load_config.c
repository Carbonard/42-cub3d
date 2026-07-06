/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_load_config.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 18:47:56 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/06 19:25:53 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	load_image(t_context *ctx, t_mlx_image *img, char *file_name)
{
	size_t	len;

	while (*file_name == ' ')
		file_name++;
	len = ft_strlen(file_name);
	if (file_name[len - 1] == '\n')
		file_name[len - 1] = 0;
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

static int	parse_color(char *str, int color[3])
{
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
	return (C3D_SUCCESS);
}

int	set_color(t_context *ctx, char *input)
{
	int	color[3];

	if (parse_color(input + 1, color) != C3D_SUCCESS)
		return (C3D_BAD_COLOR);
	if (*input == 'F')
	{
		ctx->textures.floor_set = 1;
		ctx->textures.floor = rgb(color[0], color[1], color[2]);
	}
	else
	{
		ctx->textures.ceiling_set = 1;
		ctx->textures.ceiling = rgb(color[0], color[1], color[2]);
	}
	return (C3D_SUCCESS);
}
