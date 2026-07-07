/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_read_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 17:46:13 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/07 02:17:30 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

static int	parse_line(t_context *ctx, char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
		return (load_image(ctx, &ctx->textures.north, line + 3));
	if (!ft_strncmp(line, "SO ", 3))
		return (load_image(ctx, &ctx->textures.south, line + 3));
	if (!ft_strncmp(line, "WE ", 3))
		return (load_image(ctx, &ctx->textures.west, line + 3));
	if (!ft_strncmp(line, "EA ", 3))
		return (load_image(ctx, &ctx->textures.east, line + 3));
	if (!ft_strncmp(line, "F ", 2))
		return (load_image(ctx, &ctx->textures.tex_floor, line + 2));
	if (!ft_strncmp(line, "C ", 2))
		return (load_image(ctx, &ctx->textures.tex_ceiling, line + 2));
	if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		return (set_color(ctx, line));
	while (line[0] == ' ')
		line++;
	if (*line == '\n')
		return (C3D_SUCCESS);
	if (line[0] == '1' || line [0] == '0')
		return (C3D_FINISHED_PARSER);
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = 0;
	ft_putstr_fd("Error\nInvalid line: '", 2);
	ft_putstr_fd(line, 2);
	ft_putendl_fd("'", 2);
	return (C3D_FILE_PARSER_ERROR);
}

static int	empty_element(t_context *ctx)
{
	int	ret;

	ret = 0;
	if (!(ctx->textures.north.img))
		ret += ft_putnstr_fd("Error\nMissing north texture\n", 2, 50);
	if (!(ctx->textures.south.img))
		ret += ft_putnstr_fd("Error\nMissing south texture\n", 2, 50);
	if (!(ctx->textures.west.img))
		ret += ft_putnstr_fd("Error\nMissing west texture\n", 2, 50);
	if (!(ctx->textures.east.img))
		ret += ft_putnstr_fd("Error\nMissing east texture\n", 2, 50);
	// if (!(ctx->textures.ceiling_set))
	// 	ret += ft_putnstr_fd("Error\nMissing ceiling color\n", 2, 50);
	// if (!(ctx->textures.floor_set))
	// 	ret += ft_putnstr_fd("Error\nMissing floor color\n", 2, 50);
	if (!(ctx->player.pos.x))
		ret += ft_putnstr_fd("Error\nMissing character position\n", 2, 50);
	return (ret);
}

static char	*parse_config(t_context *ctx, int fd)
{
	char		*line;
	int			status;

	line = get_next_line(fd);
	while (line)
	{
		status = parse_line(ctx, line);
		if (status == C3D_FINISHED_PARSER)
			break ;
		free(line);
		if (status != C3D_SUCCESS)
		{
			close(fd);
			close_game(ctx, status);
		}
		line = get_next_line(fd);
	}
	return (line);
}

void	parse_file(t_context *ctx, char *file_name)
{
	int			fd;
	char		*line;
	t_str_array	map;

	fd = open(file_name, O_RDONLY);
	line = parse_config(ctx, fd);
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
}
