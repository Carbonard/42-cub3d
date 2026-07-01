/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_render_screen.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 17:07:26 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/01 15:50:00 by rselva-2         ###   ########.fr       */
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
	if (!x_step && !y_step)
		return (0.5);
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

double	one(double z)
{
	(void)z;
	return (1);
}

void	display_ray(t_context *ctx, int screen_x, int height, unsigned int color)
{
	int	i;

	i = 0;
	while (i < (ctx->height - height) / 2)
	{
		put_pixel(&ctx->screen, screen_x, i, rgb(100,100,100));
		put_pixel(&ctx->screen, screen_x, ctx->height - i, rgb(200,200,200));
		i++;
	}
	i = (ctx->height - height) / 2;
	while (i < ctx->height - (ctx->height - height) / 2)
	{
		put_pixel(&ctx->screen, screen_x, i, color);
		i++;
	}
}

// void	display_minimap_segment(t_context *ctx, t_vector *u, t_vector *v)
// {

// }

void	display_miniray(t_context *ctx, t_vector *ray, unsigned int color)
{
	t_vector	p;
	double		i;

	// step = dist(&ctx->player.pos, ray) / ;
	i = 0;
	// p = ctx->player.pos;
	while (i < 1)
	{
		p.x = ctx->player.pos.x + i * (ray->x - ctx->player.pos.x);
		p.y = ctx->player.pos.y + i * (ray->y - ctx->player.pos.y);
		put_pixel(&ctx->map.img, (int)(p.x * ctx->map.scale), (int)(p.y * ctx->map.scale), color);
		i += 0.1;
	}
	put_pixel(&ctx->map.img, (int)(p.x * ctx->map.scale), (int)(p.y * ctx->map.scale), rgb(255,0,0));
}

int	on_map(t_map *map, t_vector *ray)
{
	if ((int)ray->x >= map->width || (int)ray->y >= map->height || (int)ray->x < 0 || (int)ray->y < 0)
	{
		return (0);
	}
	return (1);
}

void	minimap_point(t_map *map, t_coordinate x, t_coordinate y, unsigned int color)
{
	int a = 1;
	for (int i = -a; i < a; i++)
		for (int j = -a; j < a; j++)
			put_pixel(&map->img, (int)(x  * map->scale + i), (int)(y * map->scale + j), color);
}

void	trace_ray_2(t_context *ctx, t_vector *ray, t_vector *ray_dir, int screen_x)
{
	double			step;
	t_dist			h_dist;
	t_dist			v_dist;
	int				last_dir;
	unsigned int	color;
	int				finish = 1;
	t_vector		tmp;

	h_dist = lower_dist;
	if (ray_dir->x > 0)
	{
		h_dist = upper_dist;
	}
	v_dist = lower_dist;
	if (ray_dir->y > 0) // Maybe the other side
	{
		h_dist = upper_dist;
	}
	color = 0;
	while (finish && on_map(&ctx->map, ray) && ctx->map.matrix[(int)ray->y][(int)ray->x] == '0')
	{
		if (ray_dir->x != 0 && ray_dir->y != 0)
			step = get_step_size(ray, h_dist, v_dist);
		else
			step = 1;
		last_dir = 2;
		color = rgb(0,0,255);
		if (step > h_dist(ray->x))
		{
			color = rgb(255,0,255);
			last_dir = 1;
		}
		tmp.x = ray->x + ray_dir->x * step;
		tmp.y = ray->y + ray_dir->y * step;
		if (!on_map(&ctx->map, &tmp) || ctx->map.matrix[(int)(ray->y + step * ray_dir->y)][(int)(ray->x + step * ray_dir->x)] == '1')
		{
			step = v_dist(ray->y);
			if (last_dir == 1)
				step = h_dist(ray->x);
			step += 0.01;
			finish = 1;
		}
		ray->x += step * ray_dir->x;
		ray->y += step * ray_dir->y;
		// if (screen_x == 50)
		// minimap_point(&ctx->map, ray->x, ray->y, rgb(0,0,0));
		// mlx_put_image_to_window(ctx->mlx, ctx->window, ctx->map.img.img, 20, 20);
		// usleep(100);
		// printf("ray: (%d,%d)\nstep: %lf\nray_dir: (%lf,%lf)\n", (int)ray->x, (int)ray->y, step, ray_dir->x, ray_dir->y);
	}
	// printf("ray casted... \n");
	if (!on_map(&ctx->map, ray))
		color = rgb(255,255,0);
	// printf("ray: (%f,%f), last_dir: %d\n", ray->x, ray->y, last_dir);
	display_ray(ctx, screen_x, ctx->height / (dist(&ctx->player.pos, ray) + 1), color);
	display_miniray(ctx, ray, color);
}

// void	trace_ray_2(t_context *ctx, t_vector *ray, t_vector *ray_dir, int screen_x)
// {
// 	double			step;
// 	t_dist			h_dist;
// 	t_dist			v_dist;
// 	t_dist			h_dist_2;
// 	t_dist			v_dist_2;
// 	int				last_dir;
// 	unsigned int	color;

// 	h_dist = lower_dist;
// 	h_dist_2 = upper_dist;
// 	if (ray_dir->x > 0)
// 	{
// 		h_dist = upper_dist;
// 		h_dist_2 = lower_dist;
// 	}
// 	v_dist = lower_dist;
// 	v_dist_2 = upper_dist;
// 	if (ray_dir->y > 0) // Maybe the other side
// 	{
// 		h_dist = upper_dist;
// 		h_dist_2 = lower_dist;
// 	}
// 	color = 0;
// 	while (on_map(&ctx->map, ray) && ctx->map.matrix[(int)ray->y][(int)ray->x] == '0')
// 	{
// 		if (ray_dir->x != 0 && ray_dir->y != 0)
// 			step = get_step_size(ray, h_dist, v_dist);
// 		else
// 			step = 1;
// 		last_dir = 2;
// 		color = rgb(0,0,255);
// 		if (step > h_dist(ray->x))
// 		{
// 			color = rgb(255,0,255);
// 			last_dir = 1;
// 		}
// 		ray->x += step * ray_dir->x;
// 		ray->y += step * ray_dir->y;
// 		// if (screen_x == 50)
// 		minimap_point(&ctx->map, ray->x, ray->y, rgb(0,0,0));
// 		// printf("ray: (%d,%d)", (int)ray->x, (int)ray->y);
// 	}
// 	// printf("ray casted... \n");
// 	if (!on_map(&ctx->map, ray))
// 		color = rgb(255,255,0);
// 	if (last_dir == 1)
// 		step = h_dist_2(ray->x);
// 	else
// 		step = v_dist_2(ray->y);
// 	ray->x -= step * ray_dir->x;
// 	ray->y -= step * ray_dir->y;
// 	// printf("ray: (%f,%f), last_dir: %d\n", ray->x, ray->y, last_dir);
// 	display_ray(ctx, screen_x, ctx->height / (dist(&ctx->player.pos, ray) + 1), color);
// 	display_miniray(ctx, ray, color);
// }

void	trace_ray(t_context *ctx, int screen_x)
{
	t_vector	ray_dir;
	t_vector	ray;

	ray_dir.x = ctx->player.dir.x
		+ ((double) screen_x * 2 / (double) ctx->width - 1) * ctx->player.ort.x;
	ray_dir.y = ctx->player.dir.y
		+ ((double) screen_x * 2 / (double) ctx->width - 1) * ctx->player.ort.y;
	normalize_vector(&ray_dir);
	ray.x = ctx->player.pos.x;
	ray.y = ctx->player.pos.y;
	trace_ray_2(ctx, &ray, &ray_dir, screen_x);
}

// void	trace_ray(t_context *ctx, int screen_x)
// {
// 	t_vector	ray_dir;
// 	t_vector	ray;
// 	double		step;
// 	t_dist		h_dist;
// 	t_dist		v_dist;

// 	ray_dir.x = ctx->player.dir.x + ctx->player.ort.x;
// 	ray_dir.y = ctx->player.dir.y + ctx->player.ort.y;
// 	normalize_vector(&ray_dir);
// 	ray.x = ctx->player.pos.x;
// 	ray.y = ctx->player.pos.y;
// 	h_dist = lower_dist;
// 	if (ray_dir.x > 0)
// 		h_dist = upper_dist;
// 	v_dist = lower_dist;
// 	if (ray_dir.y > 0) // Maybe the other side
// 		h_dist = upper_dist;
// 	while (ctx->map.matrix[(int)ray.y][(int)ray.x] == '0')
// 	{
// 		if (ray_dir.x != 0 && ray_dir.y != 0)
// 			step = get_step_size(&ray, h_dist, v_dist);
// 		else
// 			step = 1;
// 		ray.x += step * ray_dir.x;
// 		ray.y += step * ray_dir.y;
// 	}
	
// }

void	render_screen(t_context *ctx)
{
	int	screen_x;
printf("Render screen\n");
	initialize_minimap(ctx);
	if (!ctx->screen.img)
	{
		printf("Creating screen with %d x %d\n", ctx->width, ctx->height);
		ctx->screen.width = ctx->width;
		ctx->screen.height = ctx->height;
		ctx->screen.img = mlx_new_image(ctx->mlx, ctx->width, ctx->height);
	}
	get_img_data(&ctx->screen);
	screen_x = 0;
	while (screen_x < ctx->width)
	{
		trace_ray(ctx, screen_x);
		screen_x += 2;
	}
	mlx_put_image_to_window(ctx->mlx, ctx->window, ctx->screen.img, 0, 0);
	mlx_put_image_to_window(ctx->mlx, ctx->window, ctx->map.img.img, 20, 20);
	mlx_put_image_to_window(ctx->mlx, ctx->window, ctx->player.minimap_img.img, 20 + ctx->player.pos.x * ctx->map.scale, 20 + ctx->player.pos.y * ctx->map.scale);
}
