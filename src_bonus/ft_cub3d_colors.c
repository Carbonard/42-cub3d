/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 17:36:26 by rselva-2          #+#    #+#             */
/*   Updated: 2026/08/09 17:36:48 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

unsigned int	rgb(int r, int g, int b)
{
	return ((r << 16) + (g << 8) + b);
}

unsigned int	argb(int a, int r, int g, int b)
{
	return ((a << 24) + (r << 16) + (g << 8) + b);
}

// This function just considers the c2 color transparency
unsigned int	merge_colors(unsigned int c1, unsigned int c2)
{
	double	a;

	a = (double)(c2 >> 24) / 0xFF;
	return (((unsigned int)((1 - a) * (c1 & RED) + a * (c2 & RED)) & RED)
		+ ((unsigned int)((1 - a) * (c1 & GREEN) + a * (c2 & GREEN)) & GREEN)
		+ ((unsigned int)((1 - a) * (c1 & BLUE) + a * (c2 & BLUE)) & BLUE));
}
