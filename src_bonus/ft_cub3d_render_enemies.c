/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_render_vertical.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 20:26:17 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/16 22:44:33 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	merge_enemy_images(t_context *ctx, t_mlx_image *other, t_enemy *enemy)
{
	int			i;
	int			j;
	t_vector	resize;

	resize.x = (double)other->width / (double)enemy->size;
	resize.y = (double)other->height / (double)enemy->size;
	j = fmax(0, -enemy->screen_pos.y);
	while (j < enemy->size && j + enemy->screen_pos.y < ctx->height)
	{
		i = fmax(0, -enemy->screen_pos.x);
		while (i < enemy->size && i + enemy->screen_pos.x < ctx->width)
		{
			if (enemy->screen_pos.x + i < ctx->width
				&& enemy->dist <= ctx->walls[enemy->screen_pos.x + i].dist)
				put_pixel(&ctx->screen,
					enemy->screen_pos.x + i, enemy->screen_pos.y + j,
					merge_colors(
						get_pixel(&ctx->screen,
							enemy->screen_pos.x + i, enemy->screen_pos.y + j),
						get_pixel(other, resize.x * i, resize.y * j)));
			i++;
		}
		j++;
	}
}

void	fill_enemy_info(t_context *ctx, t_enemy *enemy)
{
	t_vector	dir;
	double		cos;
	double		screen_factor;

	dir.x = enemy->map.x - ctx->player.pos.x;
	dir.y = enemy->map.y - ctx->player.pos.y;
	cos = v_cos(&ctx->player.dir, &dir);
	enemy->dist = dist(&ctx->player.pos, &enemy->map) * cos;
	enemy->size = (float)ctx->height / (enemy->dist);
	if (ctx->player.dir.x * dir.y < ctx->player.dir.y * dir.x)
		cos *= -1;
	screen_factor = sqrt(1 - cos * cos) / cos;
	enemy->screen_pos.x = (screen_factor + 1) * ctx->width / 2 - enemy->size / 2;
	enemy->screen_pos.y = (ctx->height - enemy->size) / 2;
	if (enemy->type == ENEMY)
		enemy->texture = ctx->textures.enemy.current;
	else
		enemy->texture = enemy->explosion->texture;
}

void	sort_enemies(t_context *ctx)
{
	int		i;
	int		j;
	t_enemy	temp;

	i = 0;
	while (i < ctx->n_enemies)
	{
		j = i + 1;
		while (j < ctx->n_enemies)
		{
			if (ctx->enemies[i].dist < ctx->enemies[j].dist)
			{
				ft_memmove(&temp, &ctx->enemies[i], sizeof(t_enemy));
				ft_memmove(&ctx->enemies[i], &ctx->enemies[j], sizeof(t_enemy));
				ft_memmove(&ctx->enemies[j], &temp, sizeof(t_enemy));
			}
			j++;
		}
		i++;
	}
}

void	check_explosions(t_context *ctx)
{
	int	i;
	int	tex;

	i = 0;
	while (i < ctx->n_explosions)
	{
		if (ctx->explosions[i].time)
		{
			tex = (get_time() - ctx->explosions[i].time) / 150000;
			if (tex < ctx->textures.explosion.size)
				ctx->explosions[i].texture = &ctx->textures.explosion.tex[tex];
			else
				ctx->map.matrix[ctx->explosions[i].map.y][ctx->explosions[i].map.x] = FLOOR;
			ctx->render = 1;
		}
		i++;
	}
}

void	render_enemies(t_context *ctx)
{
	int	i;

	check_explosions(ctx);
	i = 0;
	while (i < ctx->n_enemies)
	{
		fill_enemy_info(ctx, &ctx->enemies[i]);
		i++;
	}
	sort_enemies(ctx);
	i = 0;
	while (i < ctx->n_enemies)
	{
		merge_enemy_images(ctx, &ctx->enemies[i].texture->image, &ctx->enemies[i]);
		i++;
	}
	ctx->n_enemies = 0;
}

