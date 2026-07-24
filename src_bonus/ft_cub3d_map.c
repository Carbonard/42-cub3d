/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 22:45:56 by elangari          #+#    #+#             */
/*   Updated: 2026/07/24 13:54:42 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

static void	set_player(t_character *player, char **map, int x, int y)
{
	char	orientation;

	orientation = map[y][x];
	map[y][x] = '0';
	player->pos.x = x + 0.5;
	player->pos.y = y + 0.5;
	if (orientation == 'N')
		player->rot_ang = -M_PI / 2;
	else if (orientation == 'S')
		player->rot_ang = +M_PI / 2;
	else if (orientation == 'W')
		player->rot_ang = -M_PI;
	else if (orientation == 'E')
		player->rot_ang = 0;
	set_player_vectors(player);
}

void	add_char(char *str, char c)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	str[i] = c;
}

static int	parse_cell(t_context *ctx, t_str_array *raw_map, int x, int y)
{
	if (ft_strchr("NSWE", raw_map->data[y][x]))
		set_player(&ctx->player, raw_map->data, x, y);
	else if (raw_map->data[y][x] == ' ')
		raw_map->data[y][x] = '0';
	else if (raw_map->data[y][x] == CLOSED_DOOR)
		ctx->map.elements.doors = 1;
	else if (raw_map->data[y][x] == ENEMY)
		ctx->map.elements.enemies = 1;
	else if (raw_map->data[y][x] == EXIT)
		ctx->map.elements.exit = 1;
	else if (!ft_strchr(VALID_MAP_CHARS, raw_map->data[y][x]))
		return (1);
	return (0);
}

static int	parse_map(t_context *ctx, t_str_array *raw_map)
{
	int	i;
	int	c;

	i = 0;
	while (raw_map->data[i])
	{
		c = 0;
		while (raw_map->data[i][c] && raw_map->data[i][c] != '\n')
		{
			if (parse_cell(ctx, raw_map, c, i))
				return (1);
			c++;
		}
		if (raw_map->data[i][c] == '\n')
			raw_map->data[i][c] = 0;
		if (c > ctx->map.width)
			ctx->map.width = c;
		i++;
	}
	ctx->map.height = i;
	return (0);
}

static int	init_map(t_context *ctx, t_str_array *raw_map)
{
	int	y;
	int	x;

	ctx->map.matrix = malloc((ctx->map.height + 1) * sizeof(char *));
	if (!ctx->map.matrix)
		return (C3D_MALLOC);
	y = 0;
	while (raw_map->data[y])
	{
		ctx->map.matrix[y] = ft_str_malloc(ctx->map.width);
		if (!ctx->map.matrix[y])
			return (C3D_MALLOC);
		x = ft_strlen(raw_map->data[y]);
		ft_strlcpy(ctx->map.matrix[y], raw_map->data[y], x + 1);
		while (x < ctx->map.width)
		{
			ctx->map.matrix[y][x] = '0';
			x++;
		}
		y++;
	}
	ctx->map.matrix[y] = NULL;
	free_str_array(raw_map);
	return (0);
}

void	set_map(t_context *ctx, t_str_array *raw_map)
{
	char	**map_copy;

	if (parse_map(ctx, raw_map))
	{
		free_str_array(raw_map);
		close_game(ctx, C3D_MAP_PARSER);
	}
	if (init_map(ctx, raw_map))
	{
		free_str_array(raw_map);
		close_game(ctx, C3D_MALLOC);
	}
	map_copy = copy_matrix(ctx->map.matrix, ctx->map.height);
	if (flood_fill(map_copy, ctx->player.pos.x, ctx->player.pos.y, &ctx->map))
	{
		free_split(map_copy);
		close_game(ctx, C3D_OPEN_MAP);
	}
	free_split(map_copy);
}
