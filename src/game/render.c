/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wassim <wassim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:07:48 by wassim            #+#    #+#             */
/*   Updated: 2026/01/13 19:09:13 by wassim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * put_pixel - Place un pixel dans le buffer d'image
 */
static void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

/**
 * get_texture_color - Récupère la couleur d'un pixel de texture
 */
static int	get_texture_color(t_texture *tex, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	dst = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}

/**
 * draw_ceiling_floor - Dessine le plafond et le sol
 */
static void	draw_ceiling_floor(t_config *config)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				put_pixel(&config->img, x, y, 
					(config->ceiling.r << 16) | (config->ceiling.g << 8) | config->ceiling.b);
			else
				put_pixel(&config->img, x, y, 
					(config->floor.r << 16) | (config->floor.g << 8) | config->floor.b);
			x++;
		}
		y++;
	}
}

/**
 * draw_textured_line - Dessine une ligne verticale avec texture
 */
static void	draw_textured_line(t_config *config, int x, t_ray *ray)
{
	int		y;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		color;

	tex_x = (int)(ray->wall_x * (double)ray->texture->width);
	if ((ray->side == 0 && ray->dir_x > 0) || (ray->side == 1 && ray->dir_y < 0))
		tex_x = ray->texture->width - tex_x - 1;
	step = 1.0 * ray->texture->height / (ray->draw_end - ray->draw_start);
	tex_pos = (ray->draw_start - HEIGHT / 2 + (ray->draw_end - ray->draw_start) / 2) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos & (ray->texture->height - 1);
		tex_pos += step;
		color = get_texture_color(ray->texture, tex_x, tex_y);
		put_pixel(&config->img, x, y, color);
		y++;
	}
}

/**
 * render_frame - Rendu complet d'une frame
 */
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
