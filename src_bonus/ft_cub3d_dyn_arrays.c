/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_dyn_arrays.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 15:49:59 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/06 20:01:02 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_cub3d.h"

char	**ft_array_realloc(char **ptr, size_t size)
{
	char	**tmp;
	size_t	i;

	tmp = malloc(size * sizeof(char *));
	if (!tmp)
		return (NULL);
	i = 0;
	while (ptr && ptr[i] && i + 1 < size)
	{
		tmp[i] = ptr[i];
		i++;
	}
	tmp[i] = NULL;
	free(ptr);
	return (tmp);
}

void	init_array(t_str_array *ptr)
{
	ptr->data = NULL;
	ptr->size = 0;
	ptr->length = 0;
}

int	add_string(t_str_array *ptr, char *new)
{
	char	**tmp;

	if (ptr->length + 1 >= ptr->size)
	{
		if (!ptr->size)
			ptr->size++;
		tmp = ft_array_realloc(ptr->data, ptr->size * 2);
		if (!tmp)
			return (1);
		ptr->size *= 2;
		ptr->data = tmp;
	}
	ptr->data[ptr->length] = new;
	ptr->data[ptr->length + 1] = NULL;
	ptr->length++;
	return (0);
}

int	free_str_array(t_str_array *ptr)
{
	size_t	i;

	i = 0;
	while (i < ptr->length)
	{
		free(ptr->data[i]);
		i++;
	}
	free(ptr->data);
	return (0);
}
