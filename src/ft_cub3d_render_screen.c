/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_render_screen.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 17:07:26 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/04 00:06:15 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

typedef double (*t_dist)(double);

double	get_step_size(t_vector *ray, t_dist h_dist, t_dist v_dist)
{
	double	x_step;
	double	y_step;

	x_step = h_dist(ray->x);
	y_step = v_dist(ray->y);
	if (x_step < 0.000000001 && y_step < 0.000000001)
		return (1);
	return ((x_step + y_step) / 2);
}

double	upper_dist(double z)
{
	return (ceil(z) - z);
}

double	lower_dist(double z)
{
	return (z - floor(z));
}

void	display_ray(t_context *ctx, int screen_x, int height, unsigned int color)
{
	int	i;

	i = 0;
	if (height > ctx->height)
	{
		while (i < ctx->height)
		{
			put_pixel(&ctx->screen, screen_x, i, color);
			i++;
		}
		return ;
	}
	while (i < ctx->height)
	{
		if (i < (ctx->height - height) / 2)
			put_pixel(&ctx->screen, screen_x, i, ctx->textures.ceil);
		else if (ctx->height - i < (ctx->height - height) / 2)
			put_pixel(&ctx->screen, screen_x, i, ctx->textures.floor);
		else
			put_pixel(&ctx->screen, screen_x, i, color);
		i++;
	}
}

void	display_minimap_point(t_map *map, t_coordinate x, t_coordinate y, unsigned int color, int size)
{
	int a = size;
	for (int i = -a; i < a; i++)
		for (int j = -a; j < a; j++)
			put_pixel(&map->img, (int)(x  * map->scale + i), (int)(y * map->scale + j), color);
}

void	display_miniray(t_context *ctx, t_vector *ray, unsigned int color)
{
	t_vector	p;
	double		i;

	i = 0;
	while (i < 1)
	{
		p.x = ctx->player.pos.x + i * (ray->x - ctx->player.pos.x);
		p.y = ctx->player.pos.y + i * (ray->y - ctx->player.pos.y);
		display_minimap_point(&ctx->map, p.x, p.y, color, 2);
		i += 0.01;
	}
	put_pixel(&ctx->map.img, (int)(p.x * ctx->map.scale), (int)(p.y * ctx->map.scale), rgb(255,0,0));
}

double	screen_dist(t_character *player, t_vector *ray_dir, t_vector *point)
{
	double cos = v_cos(&player->dir, ray_dir);
	double euclidean = dist(&player->pos, point);
	return (cos * euclidean);
}

void	trace_ray_2(t_context *ctx, t_vector *ray, t_vector *ray_dir, int screen_x)
{
	double			step;
	t_dist			h_dist;
	t_dist			v_dist;
	int				last_dir;
	unsigned int	color;
	int				finish = 0;
	t_vector		tmp;

	h_dist = lower_dist;
	if (ray_dir->x > 0)
		h_dist = upper_dist;
	v_dist = lower_dist;
	if (ray_dir->y > 0)
		v_dist = upper_dist;
	color = 0;
	while (!finish && on_map(&ctx->map, ray) && ctx->map.matrix[(int)ray->y][(int)ray->x] == '0')
	{
		step = get_step_size(ray, h_dist, v_dist);
		last_dir = 2;
		if (step >= h_dist(ray->x))
		{
			last_dir = 1;
		}
		tmp.x = ray->x + ray_dir->x * step;
		tmp.y = ray->y + ray_dir->y * step;
		// display_minimap_point(&ctx->map, tmp.x, tmp.y, rgb(100,100,200), 1);
		if (!on_map(&ctx->map, &tmp))
		{
			printf("Segmentation fault (core dumped)\n");
			// Forbidden function!!
			sleep(1);
			return ;
		}
		if (is_wall(ctx, &tmp))
		{
			// 	display_minimap_point(&ctx->map, tmp.x, tmp.y, rgb(0,0,0), 1);
			if (last_dir == 2)
				step = v_dist(ray->y) / fabs(ray_dir->y);
			else if (last_dir == 1)
				step = h_dist(ray->x) / fabs(ray_dir->x);
			finish = 1;
			tmp.x = ray->x;
			color = ctx->textures.c_north;
			if (is_wall(ctx, &tmp))
				color = ctx->textures.c_west;
		}
		ray->y += step * ray_dir->y;
		ray->x += step * ray_dir->x;
	}
	// display_minimap_point(&ctx->map, ray->x, ray->y, rgb(20,20,20), 3);
	if (!on_map(&ctx->map, ray))
	{
		color = rgb(255,255,0);
		printf("fuck: (%lf,%lf)\n", ray->x, ray->y);
		sleep(4);
	}
	display_ray(ctx, screen_x, ctx->height / (screen_dist(&ctx->player, ray_dir, ray)), color);
}

void	trace_ray(t_context *ctx, int screen_x)
{
	t_vector	ray_dir;
	t_vector	ray;

	ray_dir.x = ctx->player.dir.x
		+ ((double) screen_x * 2 / (double) ctx->width - 1) * ctx->player.ort.x;
	ray_dir.y = ctx->player.dir.y
		+ ((double) screen_x * 2 / (double) ctx->width - 1) * ctx->player.ort.y;
	// t_vector O={0,0};
	// printf("before: %lf\n", dist(&O, &ray_dir));
	normalize_vector(&ray_dir);
	// printf("after: %lf\n\n", dist(&O, &ray_dir));

	ray.x = ctx->player.pos.x;
	ray.y = ctx->player.pos.y;
	trace_ray_2(ctx, &ray, &ray_dir, screen_x);
}

void	render_screen(t_context *ctx)
{
	int	screen_x;

	fill_minimap_image(&ctx->map);
	if (!ctx->screen.img)
	{
		printf("Creating screen with %d x %d\n", ctx->width, ctx->height);
		ctx->screen.width = ctx->width;
		ctx->screen.height = ctx->height;
		ctx->screen.img = mlx_new_image(ctx->mlx, ctx->width, ctx->height);
		get_img_data(&ctx->screen);
	}
	screen_x = 0;
	while (screen_x < ctx->width)
	{
		trace_ray(ctx, screen_x);
		screen_x += 1;
	}
	mlx_put_image_to_window(ctx->mlx, ctx->window, ctx->screen.img, 0, 0);
	put_minimap(ctx);
	// mlx_put_image_to_window(ctx->mlx, ctx->window, ctx->map.img.img, 20, 20);
	// mlx_put_image_to_window(ctx->mlx, ctx->window, ctx->player.minimap_img.img, 20 + ctx->player.pos.x * ctx->map.scale, 20 + ctx->player.pos.y * ctx->map.scale);
}
