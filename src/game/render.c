/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:07:48 by wassim            #+#    #+#             */
/*   Updated: 2026/01/19 12:58:58 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

typedef struct s_wall_params
{
	int					line_height;
	int					draw_start;
	int					draw_end;
}						t_wall_params;

static int	calculate_texture_x(t_ray *ray)
{
	int	tex_x;

	tex_x = (int)(ray->wall_x * (double)(ray->texture->width));
	if ((ray->side == 0 && ray->dir_x > 0) || (ray->side == 1
			&& ray->dir_y < 0))
		tex_x = ray->texture->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= ray->texture->width)
		tex_x = ray->texture->width - 1;
	return (tex_x);
}

static t_wall_params	init_wall_params(t_ray *ray)
{
	t_wall_params	params;

	params.line_height = (int)(HEIGHT / ray->perp_wall_dist);
	params.draw_start = -params.line_height / 2 + HEIGHT / 2;
	if (params.draw_start < 0)
		params.draw_start = 0;
	params.draw_end = params.line_height / 2 + HEIGHT / 2;
	if (params.draw_end >= HEIGHT)
		params.draw_end = HEIGHT - 1;
	return (params);
}

static void	draw_wall_column(t_config *config, int x, t_ray *ray,
		t_wall_params params)
{
	int		y;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;

	tex_x = calculate_texture_x(ray);
	step = 1.0 * ray->texture->height / params.line_height;
	tex_pos = (params.draw_start - HEIGHT / 2 + params.line_height / 2) * step;
	y = params.draw_start;
	while (y <= params.draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= ray->texture->height)
			tex_y = ray->texture->height - 1;
		put_pixel(&config->img, x, y, get_texture_color(ray->texture, tex_x,
				tex_y));
		tex_pos += step;
		y++;
	}
}

static void	draw_textured_line(t_config *config, int x, t_ray *ray)
{
	t_wall_params	params;

	params = init_wall_params(ray);
	draw_wall_column(config, x, ray, params);
}

int	render_frame(t_config *config)
{
	int		x;
	t_ray	ray;

	draw_ceiling_floor(config);
	x = 0;
	while (x < WIDTH)
	{
		cast_ray(config, x, &ray);
		draw_textured_line(config, x, &ray);
		x++;
	}
	mlx_put_image_to_window(config->mlx, config->win, config->img.img, 0, 0);
	return (0);
}
