/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wassim <wassim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:06:53 by wassim            #+#    #+#             */
/*   Updated: 2026/01/13 19:07:11 by wassim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * init_ray - Initialise les paramètres d'un rayon
 */
static void	init_ray(t_ray *ray, t_config *config, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIDTH - 1;
	ray->dir_x = cos(config->player.angle) + sin(config->player.angle) * camera_x * tan(FOV / 2);
	ray->dir_y = sin(config->player.angle) - cos(config->player.angle) * camera_x * tan(FOV / 2);
	ray->map_x = (int)config->player.x;
	ray->map_y = (int)config->player.y;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
}

/**
 * set_step - Définit la direction et la distance initiale du rayon
 */
static void	set_step(t_ray *ray, t_config *config)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (config->player.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - config->player.x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (config->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - config->player.y) * ray->delta_dist_y;
	}
}

/**
 * perform_dda - Algorithme DDA pour trouver le mur
 */
static void	perform_dda(t_ray *ray, t_config *config)
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
		if (ray->map_y < 0 || ray->map_y >= config->map.height ||
			ray->map_x < 0 || ray->map_x >= config->map.width)
			break;
		if (config->map.grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

/**
 * calculate_wall_dist - Calcule la distance perpendiculaire au mur
 */
static void	calculate_wall_dist(t_ray *ray, t_config *config)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - config->player.x + 
			(1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - config->player.y + 
			(1 - ray->step_y) / 2) / ray->dir_y;
}

/**
 * calculate_line_height - Calcule la hauteur de la ligne à dessiner
 */
static void	calculate_line_height(t_ray *ray)
{
	int	line_height;

	if (ray->perp_wall_dist < 0.1)
		ray->perp_wall_dist = 0.1;
	line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

/**
 * get_wall_x - Calcule la coordonnée X sur le mur touché
 */
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

/**
 * get_texture - Sélectionne la texture selon l'orientation du mur
 */
static t_texture	*get_texture(t_ray *ray, t_config *config)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return (&config->tex_west);
		else
			return (&config->tex_east);
	}
	else
	{
		if (ray->dir_y > 0)
			return (&config->tex_north);
		else
			return (&config->tex_south);
	}
}

/**
 * cast_ray - Lance un rayon et retourne les informations de collision
 */
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
