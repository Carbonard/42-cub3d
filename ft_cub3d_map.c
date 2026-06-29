/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 22:45:56 by elangari          #+#    #+#             */
/*   Updated: 2026/06/29 16:22:26 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

static void	set_player(t_character *player, char **map, int x, int y)
{
	char	orientation;

	orientation = map[y][x];
	map[y][x] = '0';
	player->pos.x = x;
	player->pos.y = y;
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

static int	parse_map(t_context *ctx, t_str_array *raw_map)
{
	int i;
	int c;

	i = 0;
	while(raw_map->data[i])
	{
		c = 0;
		while (raw_map->data[i][c] && raw_map->data[i][c] != '\n')
		{
			if (ft_strchr("NSWE", raw_map->data[i][c]))
				set_player(&ctx->player, raw_map->data, c, i);
			else if (raw_map->data[i][c] == ' ')
				raw_map->data[i][c] = '0';
			else if (raw_map->data[i][c] != '1' && raw_map->data[i][c] != '0')
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
	int y;
	int	x;

	if (!(ctx->map.matrix = malloc((ctx->map.height + 1) * sizeof(char *))))
		return (1);
	y = 0;
	while (raw_map->data[y])
	{
		if (!(ctx->map.matrix[y] = ft_str_malloc(ctx->map.width)))
			return (1);
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

static int	flood_fill(char **map, int x, int y, int width, int height)
{
	int	ret;

	if (x < 0 || x >= width || y < 0 || y >= height)
		return (1);
	if (map[y][x] == '1')
		return (0);
	ret = 0;
	map[y][x] = '1';
	if (flood_fill(map, x + 1, y, width, height))
		ret = 1;
	else if (flood_fill(map, x - 1, y, width, height))
		ret = 1;
	else if (flood_fill(map, x, y + 1, width, height))
		ret = 1;
	else if (flood_fill(map, x, y - 1, width, height))
		ret = 1;
	return (ret);
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
	for (int i = 0; ctx->map.matrix[i]; i++)
		printf("%s\n", ctx->map.matrix[i]);
	map_copy = copy_matrix(ctx->map.matrix, ctx->map.height);
	if (flood_fill(map_copy, ctx->player.pos.x, ctx->player.pos.y, ctx->map.width, ctx->map.height))
	{
		free_split(map_copy);
		close_game(ctx, C3D_OPEN_MAP);
	}
	free_split(map_copy);
}
