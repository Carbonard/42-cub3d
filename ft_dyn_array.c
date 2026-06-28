/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dyn_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elangari <elangari@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 15:49:59 by rselva-2          #+#    #+#             */
/*   Updated: 2026/06/28 17:43:16 by elangari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_cub3d.h"

char	**emergency_exit(char **ptr)
{
	int i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}

char	**ft_array_realloc(char **ptr, size_t size)
{
	char	**tmp;
	size_t	i;

	tmp = malloc(size * sizeof(char *));
	if (!tmp)
		return (emergency_exit(ptr));
	while (ptr[i] && i + 1 < size)
	{
		tmp[i] = ptr[i];
		i++;
	}
	tmp[i] = NULL;
	free(ptr);
	return (tmp);
}

void	init_string(t_str_array *ptr)
{
	ptr->data = NULL;
	ptr->size = 0;
	ptr->length = 0;
}

int		add_string(t_str_array *ptr, char *new)
{
	char	**tmp;

	if (ptr->length + 1 >= ptr->size)
	{
		if (!ptr->size)
			ptr->size++;
		tmp = ft_array_realloc(ptr->data, ptr->size * 2);
		if (!tmp)
			return 1;
		ptr->size *= 2;
		ptr->data = tmp;
	}
	ptr->data[ptr->length] = new;
	ptr->data[ptr->length + 1] = NULL;
	ptr->length++;
	return (0);
}

int	string_delete(t_str_array *ptr)
{
	size_t i;

	i = 0;
	while (i < ptr->length)
	{
		free(ptr->data[i]);
		i++;
	}
	free(ptr->data);
	return (0);
}
