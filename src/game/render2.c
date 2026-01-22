/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 20:50:51 by ainthana          #+#    #+#             */
/*   Updated: 2026/01/18 20:50:51 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_texture_color(t_texture *tex, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	dst = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}

void	draw_ceiling_floor(t_config *config)
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
				put_pixel(&config->img, x, y, (config->ceiling.r << 16)
					| (config->ceiling.g << 8) | config->ceiling.b);
			else
				put_pixel(&config->img, x, y, (config->floor.r << 16)
					| (config->floor.g << 8) | config->floor.b);
			x++;
		}
		y++;
	}
}

void	free_config_two(t_config *cfg)
{
	if (cfg->textures.north)
		free(cfg->textures.north);
	if (cfg->textures.south)
		free(cfg->textures.south);
	if (cfg->textures.west)
		free(cfg->textures.west);
	if (cfg->textures.east)
		free(cfg->textures.east);
}
