/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wassim <wassim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:03:01 by wassim            #+#    #+#             */
/*   Updated: 2026/01/13 19:03:59 by wassim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"


static int	ft_init_mlx_connection(t_config *config)
{
	config->mlx = mlx_init();
	if (!config->mlx)
	{
		printf("Error\nFailed to initialize MLX\n");
		return (0);
	}
	return (1);
}


static int	ft_create_window(t_config *config)
{
	config->win = mlx_new_window(config->mlx, WIDTH, HEIGHT, "cub3D");
	if (!config->win)
	{
		printf("Error\nFailed to create window\n");
		return (0);
	}
	return (1);
}

static int	ft_load_single_texture(t_config *config, char *path, t_texture *tex)
{
	tex->img = mlx_xpm_file_to_image(config->mlx, path, 
		&tex->width, &tex->height);
	if (!tex->img)
	{
		printf("Error\nFailed to load texture: %s\n", path);
		return (0);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
		&tex->line_len, &tex->endian);
	if (!tex->addr)
	{
		printf("Error\nFailed to get texture data: %s\n", path);
		return (0);
	}
	return (1);
}


static int	ft_load_all_textures(t_config *config)
{
	if (!ft_load_single_texture(config, config->textures.north,
		&config->tex_north))
		return (0);
	if (!ft_load_single_texture(config, config->textures.south,
		&config->tex_south))
		return (0);
	if (!ft_load_single_texture(config, config->textures.west,
		&config->tex_west))
		return (0);
	if (!ft_load_single_texture(config, config->textures.east,
		&config->tex_east))
		return (0);
	return (1);
}


static int	ft_create_image_buffer(t_config *config)
{
	config->img.img = mlx_new_image(config->mlx, WIDTH, HEIGHT);
	if (!config->img.img)
	{
		printf("Error\nFailed to create image buffer\n");
		return (0);
	}
	config->img.addr = mlx_get_data_addr(config->img.img,
		&config->img.bpp, &config->img.line_len, &config->img.endian);
	if (!config->img.addr)
	{
		printf("Error\nFailed to get image data\n");
		return (0);
	}
	return (1);
}


int	init_mlx(t_config *config)
{
	if (!ft_init_mlx_connection(config))
		return (0);
	if (!ft_create_window(config))
		return (0);
	if (!ft_load_all_textures(config))
		return (0);
	if (!ft_create_image_buffer(config))
		return (0);
	return (1);
}
