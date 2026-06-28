/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elangari <elangari@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 22:45:56 by elangari          #+#    #+#             */
/*   Updated: 2026/06/28 17:44:27 by elangari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

// read_file
// init data //
// init map
// 



int	parse_map(t_context *ctx, t_str_array *og_map)
{
	int i;
	int c;

	i = 0;
	while(og_map->data[i])
	{
		c = 0;
		while (og_map->data[i][c])
		{
			if (og_map->data[i][c] == " ")
				og_map->data[i][c] = "0";
			else if (og_map->data[i][c] == "N" || og_map->data[i][c] == "S"
				|| og_map->data[i][c] == "W" || og_map->data[i][c] == "E")
				set_player();
			else if (og_map->data[i][c] != "1" && og_map->data[i][c] != "0")
				return (1);
			c++;
		}
		if ((c + 1) > ctx->map.width)
			ctx->map.width = c + 1;
		i++;
	}
	ctx->map.height = i + 1;
	return (0);
}

int	init_map(t_context *ctx, t_str_array *map)
{
	int y;
	int	x;

	y = 0;
	if (!(ctx->map.matrix = malloc(ctx->map.height + 1 * sizeof(char *))))
		return 1;
	while (map->data[y])
	{
		x = 0;
		if (!(ctx->map.matrix[y] = ft_calloc(ctx->map.width + 1, sizeof(char))))
			return (emergency_exit(ctx->map.matrix), 1);
		while (map->data[y][x])
		{
			ctx->map.matrix[y][x] = map->data[y][x];
			x++;
		}
		while (x < ctx->map.width)
		{
			ctx->map.matrix[y][x] = "0";
			x++;
		}
		y++;
	}
	string_delete(map);
}

char	*get_map(t_context *ctx, char *file_name)
{
	int 		fd;
	int			x;
	char		*tmp;
	t_str_array	map;

	fd = open(file_name, O_RDONLY);
	init_string(map);
	while ((tmp = get_next_line(fd)) > 0)
	{
		if (add_string(&map, tmp))
			return NULL;
	}
	if (parse_map(&map))
		return NULL;
	init_map(ctx, &map, x);
}
