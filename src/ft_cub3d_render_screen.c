/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d_render_screen.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rselva-2 <rselva-2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 17:07:26 by rselva-2          #+#    #+#             */
/*   Updated: 2026/07/04 21:08:28 by rselva-2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

typedef double (*t_dist)(double);

typedef struct	s_axis_distances
{
	t_dist	horizontal;
	t_dist	vertical;
}	t_axis_dist;

double	get_step_size(t_vector *ray_pos, t_axis_dist *d)
{
	double	x_step;
	double	y_step;

	x_step = d->horizontal(ray_pos->x);
	y_step = d->vertical(ray_pos->y);
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

	if (texture == &ctx->textures.north || texture == &ctx->textures.south)
		texture_coord_x = lower_dist(wall_point->x) * (double)texture->width;
	else
		texture_coord_x = lower_dist(wall_point->y) * (double)texture->width;
	texture_coord_y = (screen_y - ((double)ctx->height - wall_height) / 2) * texture->height / wall_height;
	return (get_pixel(texture, texture_coord_x, texture_coord_y));
}

void	display_vertical_slice(t_context *ctx,
			int screen_x, t_mobile_vector *ray, t_mlx_image *texture)
{
	int				i;
	int				wall_height;
	unsigned int	color;

	if (!texture)
	{
		printf("Debug: missing texture (display_vertical_slice)\n");
		return ;
	}
	i = 0;
	wall_height = ctx->height / (screen_dist(&ctx->player, ray));
	while (i < ctx->height)
	{
		if (ctx->rain_mode && get_time() % ctx->rain_mode == 0)
			put_pixel(&ctx->screen, screen_x, i, rgb(16, 71, 192));
		else if (i <= (ctx->height - wall_height) / 2)
			put_pixel(&ctx->screen, screen_x, i, ctx->textures.ceil);
		else if (ctx->height - i <= (ctx->height - wall_height) / 2)
			put_pixel(&ctx->screen, screen_x, i, ctx->textures.floor);
		else
		{
			color = get_texture_pixel(ctx, texture, wall_height, i, &ray->pos);
			put_pixel(&ctx->screen, screen_x, i, color);
		}
		i++;
	}
}

t_mlx_image	*last_step(t_context *ctx, double last_step, t_mobile_vector *ray, t_axis_dist *d, t_vector *last_jump)
{
	if (last_step < d->horizontal(ray->pos.x))
		last_step = d->vertical(ray->pos.y) / fabs(ray->dir.y);
	else
		last_step = d->horizontal(ray->pos.x) / fabs(ray->dir.x);
	last_jump->x = ray->pos.x;
	ray->pos.y += last_step * ray->dir.y;
	ray->pos.x += last_step * ray->dir.x;
	if (!is_wall(ctx, last_jump))
	{
		if (ray->dir.x > 0)
			return (&ctx->textures.east);
		else
			return (&ctx->textures.west);
	}
	else
	{
		if (ray->dir.y > 0)
			return (&ctx->textures.south);
		else
			return (&ctx->textures.north);
	}
}

void	trace_ray_2(t_context *ctx,
			t_mobile_vector *ray, t_axis_dist *d, int screen_x)
{
	double			step;
	t_mlx_image		*texture;
	t_vector		tmp;

	while (on_map(&ctx->map, &ray->pos) && ctx->map.matrix[(int)ray->pos.y][(int)ray->pos.x] == '0')
	{
		step = get_step_size(&ray->pos, d);
		tmp.x = ray->pos.x + ray->dir.x * step;
		tmp.y = ray->pos.y + ray->dir.y * step;
		if (!on_map(&ctx->map, &tmp))
		{
			printf("Segmentation fault (core dumped)\n");
			return ;
		}
		if (is_wall(ctx, &tmp))
		{
			texture = last_step(ctx, step, ray, d, &tmp);
			break ;
		}
		ray->pos.y += step * ray->dir.y;
		ray->pos.x += step * ray->dir.x;
	}
	if (!on_map(&ctx->map, &ray->pos))
		texture = NULL;
	display_vertical_slice(ctx, screen_x, ray, texture);
}

void	trace_ray(t_context *ctx, int screen_x)
{
	t_mobile_vector			ray;
	double					scale_screen_factor;
	struct s_axis_distances	distances;

	scale_screen_factor = (double) screen_x * 2 / (double) ctx->width - 1;
	ray.dir.x = ctx->player.dir.x + scale_screen_factor * ctx->player.ort.x;
	ray.dir.y = ctx->player.dir.y + scale_screen_factor * ctx->player.ort.y;
	normalize_vector(&ray.dir);
	ray.pos.x = ctx->player.pos.x;
	ray.pos.y = ctx->player.pos.y;
	if (ray.dir.x > 0)
		distances.horizontal = upper_dist;
	else
		distances.horizontal = lower_dist;
	if (ray.dir.y > 0)
		distances.vertical = upper_dist;
	else
		distances.vertical = lower_dist;
	trace_ray_2(ctx, &ray, &distances, screen_x);
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
		screen_x++;
	}
	mlx_put_image_to_window(ctx->mlx, ctx->window, ctx->screen.img, 0, 0);
	put_minimap(ctx);
}
