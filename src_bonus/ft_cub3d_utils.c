/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 16:21:53 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/20 16:47:42 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

char	**copy_matrix(char **matrix, size_t size)
{
	char	**copy;
	size_t	i;

	copy = malloc((size + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < size)
	{
		copy[i] = ft_strdup(matrix[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int	flood_fill(char **map, int x, int y, t_map *size)
{
	int	ret;

	if (x < 0 || x >= size->width || y < 0 || y >= size->height)
		return (1);
	if (map[y][x] == '1')
		return (0);
	ret = 0;
	map[y][x] = '1';
	if (flood_fill(map, x + 1, y, size))
		ret = 1;
	else if (flood_fill(map, x - 1, y, size))
		ret = 1;
	else if (flood_fill(map, x, y + 1, size))
		ret = 1;
	else if (flood_fill(map, x, y - 1, size))
		ret = 1;
	return (ret);
}

size_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000 + tv.tv_usec);
}
