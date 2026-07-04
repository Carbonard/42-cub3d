/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_render_screen.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 17:07:26 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/04 02:04:37 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

typedef double (*t_dist)(double);

double	get_step_size(t_vector *ray_pos, t_dist h_dist, t_dist v_dist)
{
	double	x_step;
	double	y_step;

	x_step = h_dist(ray_pos->x);
	y_step = v_dist(ray_pos->y);
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

double	screen_dist(t_character *player, t_mobile_vector *ray)
{
	double cos = v_cos(&player->dir, &ray->dir);
	double euclidean = dist(&player->pos, &ray->pos);
	return (cos * euclidean);
}

unsigned int	get_texture_pixel(t_context *ctx, t_mlx_image *texture, int wall_height, int screen_y, t_vector *wall_point)
{
	double	texture_coord_y;
	double	texture_coord_x;

	// printf("%lf, %lf\n", wall_point->x, wall_point->y);
	if (texture == &ctx->textures.north || texture == &ctx->textures.south)
		texture_coord_x = lower_dist(wall_point->x) * (double)texture->width;
	else
		texture_coord_x = lower_dist(wall_point->y) * (double)texture->width;
	texture_coord_y = (screen_y - ((double)ctx->height - wall_height) / 2) * texture->height / wall_height;
	return (get_pixel(texture, texture_coord_x, texture_coord_y));
}

void	display_ray(t_context *ctx, int screen_x, t_mobile_vector *ray, t_mlx_image *texture)
{
	int				i;
	int				height;
	unsigned int	color;

	if (texture == &ctx->textures.north)
		color = ctx->textures.c_north;
	if (texture == &ctx->textures.west)
		color = ctx->textures.c_west;
	i = 0;
	height = ctx->height / (screen_dist(&ctx->player, ray));
	// if (height > ctx->height)
	// {
	// 	while (i < ctx->height)
	// 	{
	// 		put_pixel(&ctx->screen, screen_x, i, color);
	// 		i++;
	// 	}
	// 	return ;
	// }
	while (i < ctx->height)
	{
		if (i < (ctx->height - height) / 2)
			put_pixel(&ctx->screen, screen_x, i, ctx->textures.ceil);
		else if (ctx->height - i < (ctx->height - height) / 2)
			put_pixel(&ctx->screen, screen_x, i, ctx->textures.floor);
		else
		{
			color = get_texture_pixel(ctx, texture, height, i, &ray->pos);
			put_pixel(&ctx->screen, screen_x, i, color);
		}
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

void	display_miniray(t_context *ctx, t_mobile_vector *ray, unsigned int color)
{
	t_vector	p;
	double		i;

	i = 0;
	while (i < 1)
	{
		p.x = ctx->player.pos.x + i * (ray->pos.x - ctx->player.pos.x);
		p.y = ctx->player.pos.y + i * (ray->pos.y - ctx->player.pos.y);
		display_minimap_point(&ctx->map, p.x, p.y, color, 2);
		i += 0.01;
	}
	put_pixel(&ctx->map.img, (int)(p.x * ctx->map.scale), (int)(p.y * ctx->map.scale), rgb(255,0,0));
}

void	trace_ray_2(t_context *ctx, t_mobile_vector *ray, int screen_x)
{
	double			step;
	t_dist			h_dist;
	t_dist			v_dist;
	int				last_dir;
	t_mlx_image		*texture;
	int				finish = 0;
	t_vector		tmp;

	h_dist = lower_dist;
	if (ray->dir.x > 0)
		h_dist = upper_dist;
	v_dist = lower_dist;
	if (ray->dir.y > 0)
		v_dist = upper_dist;
	while (!finish && on_map(&ctx->map, &ray->pos) && ctx->map.matrix[(int)ray->pos.y][(int)ray->pos.x] == '0')
	{
		step = get_step_size(&ray->pos, h_dist, v_dist);
		last_dir = 2;
		if (step >= h_dist(ray->pos.x))
		{
			last_dir = 1;
		}
		tmp.x = ray->pos.x + ray->dir.x * step;
		tmp.y = ray->pos.y + ray->dir.y * step;
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
				step = v_dist(ray->pos.y) / fabs(ray->dir.y);
			else if (last_dir == 1)
				step = h_dist(ray->pos.x) / fabs(ray->dir.x);
			finish = 1;
			tmp.x = ray->pos.x;
			if (!is_wall(ctx, &tmp))
			{
				if (ray->dir.x > 0)
					texture = &ctx->textures.east;
				else
					texture = &ctx->textures.west;
			}
			else
			{
				if (ray->dir.y > 0)
					texture = &ctx->textures.south;
				else
					texture = &ctx->textures.north;
			}
		}
		ray->pos.y += step * ray->dir.y;
		ray->pos.x += step * ray->dir.x;
	}
	// display_minimap_point(&ctx->map, ray->pos.x, ray->pos.y, rgb(20,20,20), 3);
	if (!on_map(&ctx->map, &ray->pos))
	{
		texture = NULL;
		printf("fuck: (%lf,%lf)\n", ray->pos.x, ray->pos.y);
		sleep(4);
	}
	display_ray(ctx, screen_x, ray, texture);
}

void	trace_ray(t_context *ctx, int screen_x)
{
	t_mobile_vector	ray;

	ray.dir.x = ctx->player.dir.x
		+ ((double) screen_x * 2 / (double) ctx->width - 1) * ctx->player.ort.x;
	ray.dir.y = ctx->player.dir.y
		+ ((double) screen_x * 2 / (double) ctx->width - 1) * ctx->player.ort.y;
	// t_vector O={0,0};
	// printf("before: %lf\n", dist(&O, &ray_dir));
	normalize_vector(&ray.dir);
	// printf("after: %lf\n\n", dist(&O, &ray_dir));

	ray.pos.x = ctx->player.pos.x;
	ray.pos.y = ctx->player.pos.y;
	trace_ray_2(ctx, &ray, screen_x);
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
