/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2026/01/18 20:46:10 by ainthana          #+#    #+#             */
/*   Updated: 2026/01/18 20:46:10 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_ray(t_ray *ray, t_config *config, int x)
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;

	camera_x = -(2.0 * x / (double)WIDTH - 1.0);
	dir_x = cos(config->player.angle);
	dir_y = sin(config->player.angle);
	plane_x = -sin(config->player.angle);
	plane_y = cos(config->player.angle);
	ray->dir_x = dir_x + plane_x * camera_x;
	ray->dir_y = dir_y + plane_y * camera_x;
	ray->map_x = (int)config->player.x;
	ray->map_y = (int)config->player.y;
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->dir_y);
	ray->hit = 0;
}

void	set_step(t_ray *ray, t_config *config)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (config->player.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - config->player.x)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (config->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - config->player.y)
			* ray->delta_dist_y;
	}
}

void	perform_dda(t_ray *ray, t_config *config)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0 || ray->map_y >= config->map.height || ray->map_x < 0
			|| ray->map_x >= config->map.width)
			break ;
		if (config->map.grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}
