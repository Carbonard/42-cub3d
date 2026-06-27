/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elangari <elangari@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 15:49:59 by rselva-2          #+#    #+#             */
/*   Updated: 2026/06/27 19:44:45 by elangari         ###   ########.fr       */
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

char	**ft_array_realloc(char **ptr, int size)
{
	char	**tmp;
	int i;

	tmp = malloc(size * sizeof(char *));
	if (!tmp)
		return (emergency_exit(ptr));
	while (ptr[i] && i < size)
	{
		tmp[i] = ptr[i];
		i++;
	}
	tmp[i] = NULL;
	free(ptr);
	return (tmp);
}

void	init_string(t_string *ptr)
{
	ptr->data = NULL;
	ptr->size = 0;
	ptr->length = 0;
}

int		string_pushback(t_string *ptr, char *new)
{
	char	**tmp;
	// int i;

	// i = 0;
	if (ptr->length + 2 >= ptr->size)
	{
		if (!ptr->size)
			ptr->size++;
		ptr->size *= 2;
		tmp = ft_array_realloc(ptr->data, ptr->size);
		if (!tmp)
			return 1;
		ptr->data = tmp;
	}
	ptr->data[ptr->length] = new;
	ptr->data[ptr->length + 1] = NULL;
	return (0);
}


int	string_delete(t_string *ptr)
{
	int i;

	i = ptr->length;
	while (ptr->data[i])
	{
		free(ptr->data[i]);
		i++;
	}
	free(ptr->data);
	return (0);
}
