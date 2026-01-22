/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:06:53 by wassim            #+#    #+#             */
/*   Updated: 2026/01/22 13:58:30 by wbaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	calculate_wall_dist(t_ray *ray, t_config *config)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - config->player.x + (1.0
					- ray->step_x) / 2.0) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - config->player.y + (1.0
					- ray->step_y) / 2.0) / ray->dir_y;
	if (ray->perp_wall_dist < 0.01)
		ray->perp_wall_dist = 0.01;
}

static void	calculate_line_height(t_ray *ray)
{
	int	line_height;

	line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

static double	get_wall_x(t_ray *ray, t_config *config)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = config->player.y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = config->player.x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

static t_texture	*get_texture(t_ray *ray, t_config *config)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return (&config->tex_east);
		else
			return (&config->tex_west);
	}
	else
	{
		if (ray->dir_y > 0)
			return (&config->tex_south);
		else
			return (&config->tex_north);
	}
}

void	cast_ray(t_config *config, int x, t_ray *ray)
{
	init_ray(ray, config, x);
	set_step(ray, config);
	perform_dda(ray, config);
	calculate_wall_dist(ray, config);
	calculate_line_height(ray);
	ray->wall_x = get_wall_x(ray, config);
	ray->texture = get_texture(ray, config);
}
