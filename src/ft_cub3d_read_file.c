/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_read_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elangari <elangari@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 17:46:13 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/04 21:44:35 by elangari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	load_image(t_context *ctx, t_mlx_image *image, char *file_name)
{
	size_t	len;

	len = ft_strlen(file_name);
	if (file_name[len - 1] == '\n')
		file_name[len - 1] = 0;
	printf("Loading image '%s'\n", file_name);
	image->img = mlx_xpm_file_to_image(ctx->mlx, file_name, &image->width, &image->height);
	if (!image->img)
		return (C3D_FILE_PARSER_ERROR);
	get_img_data(image);
	return (C3D_SUCCESS);
}

// int	load_color(t_context *ctx, unsigned int *color, char *file_name)
// {
// 	*color = 42;
// 	(void) file_name;
// 	return (C3D_SUCCESS);
// }

int parse_color(char *str, int color[3])
{
	int cnt;

	cnt = 0;
	while(*str == ' ')
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

int set_color(t_context *ctx, char *input)
{
	int	color[3];

	if (parse_color(input + 1, color) != C3D_SUCCESS)
		return (C3D_BAD_COLOR);
	printf("fine\n");
	if (*input == 'F')
	{
		ctx->textures.floor_set = 1;
		ctx->textures.floor = rgb(color[0], color[1], color[2]);
	}
	else
	{
		ctx->textures.ceil_set = 1;
		ctx->textures.ceil = rgb(color[0], color[1], color[2]);
	}
	return (C3D_SUCCESS);
}

int	parse_line(t_context *ctx, char *line)
{
	printf("Line = %s...\n", line);
	if (!ft_strncmp(line, "NO ", 3))
		return (load_image(ctx, &ctx->textures.north, line + 3));
	if (!ft_strncmp(line, "SO ", 3))
		return (load_image(ctx, &ctx->textures.south, line + 3));
	if (!ft_strncmp(line, "WE ", 3))
		return (load_image(ctx, &ctx->textures.west, line + 3));
	if (!ft_strncmp(line, "EA ", 3))
		return (load_image(ctx, &ctx->textures.east, line + 3));
	if (!ft_strncmp(line, "F ", 2))
		return (set_color(ctx, line));
	if (!ft_strncmp(line, "C ", 2))
		return (set_color(ctx, line));
	while (line[0] == ' ')
		line++;
	if (*line == '\n')
		return(C3D_SUCCESS);
	if (line[0] == '1' || line [0] == '0')
		return (C3D_FINISHED_PARSER);
	printf("help\n");
	return (C3D_FILE_PARSER_ERROR);
}

int	empty_element(t_context *ctx)
{
	int ret;

	ret = 0;
	if (!(ctx->textures.north.img))
		ret += ft_putnstr_fd("Error\nMissing north texture\n", 2, 50);
	if (!(ctx->textures.south.img))
		ret += ft_putnstr_fd("Error\nMissing south texture\n", 2, 50);
	if (!(ctx->textures.west.img))
		ret += ft_putnstr_fd("Error\nMissing west texture\n", 2, 50);
	if (!(ctx->textures.east.img))
		ret += ft_putnstr_fd("Error\nMissing east texture\n", 2, 50);
	if (!(ctx->textures.ceil_set))	
		ret += ft_putnstr_fd("Error\nMissing ceiling color\n", 2, 50);
	if (!(ctx->textures.floor_set))	
		ret += ft_putnstr_fd("Error\nMissing floor color\n", 2, 50);
	if (!(ctx->player.pos.x))
		ret += ft_putnstr_fd("Error\nMissing character position\n", 2, 50);
	return (ret);
}

void	read_file(t_context *ctx, char *file_name)
{
	int			fd;
	char		*line;
	int			status;
	t_str_array	map;

	fd = open(file_name, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		status = parse_line(ctx, line);
		if (status == C3D_FINISHED_PARSER)
			break ;
		free(line);
		if (status == C3D_FILE_PARSER_ERROR)
		{
			close(fd);
			close_game(ctx, status);
		}
		line = get_next_line(fd);
	}
	init_array(&map);
	while (line)
	{
		add_string(&map, line);
		line = get_next_line(fd);
	}
	close(fd);
	set_map(ctx, &map);
	if (empty_element(ctx))
		close_game(ctx, C3D_EMPTY_FIELD);
	for (int i = 0; ctx->map.matrix[i]; i++)
	{
		puts(ctx->map.matrix[i]);
	}
}
