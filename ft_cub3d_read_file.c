/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_read_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 17:46:13 by rselva-2          #+#    #+#             */
/*   Updated: 2026/06/29 14:58:24 by rselva-2         ###   ########.fr       */
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

int	load_color(int *color, char *file_name)
{
	*color = 42;
	(void) file_name;
	return (C3D_SUCCESS);
}

int	parse_line(t_context *ctx, char *line)
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
		return (load_color(&ctx->textures.floor, line + 3));
	if (!ft_strncmp(line, "C ", 2))
		return (load_color(&ctx->textures.ceil, line + 3));
	while (line [0] == ' ')
		line++;
	if (line[0] == '1' || line [0] == '0')
		return (C3D_FINISHED_PARSER);
	return (C3D_FILE_PARSER_ERROR);
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
	for (int i = 0; ctx->map.matrix[i]; i++)
	{
		puts(ctx->map.matrix[i]);
	}
}
