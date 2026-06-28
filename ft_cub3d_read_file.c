/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_read_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 17:46:13 by rselva-2          #+#    #+#             */
/*   Updated: 2026/06/28 17:47:26 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

enum	e_states
{
	PARSE_SUCCESS,
	PARSE_ERROR,
	PARSE_FINISHED
};

int	load_image(t_context *ctx, t_mlx_image *image, char *file_name)
{
	image->img = mlx_xpm_file_to_image(ctx->mlx, file_name, &image->width, &image->height);
	if (!image->img)
		return (PARSE_ERROR);
	get_img_data(image);
	return (PARSE_SUCCESS);
}

int	parse_line(t_context *ctx, char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
		return (load_image(ctx, &ctx->visuals.north, line + 3));
	if (!ft_strncmp(line, "SO ", 3))
		return (load_image(ctx, &ctx->visuals.south, line + 3));
	if (!ft_strncmp(line, "WE ", 3))
		return (load_image(ctx, &ctx->visuals.west, line + 3));
	if (!ft_strncmp(line, "EA ", 3))
		return (load_image(ctx, &ctx->visuals.east, line + 3));
	if (!ft_strncmp(line, "F ", 2))
		return (load_color(ctx, &ctx->visuals.floor, line + 3));
	if (!ft_strncmp(line, "C ", 2))
		return (load_color(ctx, &ctx->visuals.ceil, line + 3));
	while (line [0] == ' ')
		line++;
	if (line[0] == '1' || line [0] == '0')
		return (PARSE_FINISHED);
	return (PARSE_ERROR);
}

void	read_file(t_context *ctx, char *file_name)
{
	int		fd;
	char	*line;
	int		status;

	fd = open(file_name, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		status = parse_line(ctx, line);
		if (status == PARSE_ERROR)
			close_game(ctx);
		if (status == PARSE_FINISHED)
			break ;
		line = get_next_line(fd);
	}
	while (line)
	{
		add_string(&ctx->map, line);
		line = get_next_line(fd);
	}
	parse_map(ctx, &ctx->map);
}
