/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 20:53:23 by ainthana          #+#    #+#             */
/*   Updated: 2026/01/18 20:53:23 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_create_window(t_config *config)
{
	config->win = mlx_new_window(config->mlx, WIDTH, HEIGHT, "cub3D");
	if (!config->win)
	{
		printf("Error\nFailed to create window\n");
		return (0);
	}
	return (1);
}

int	ft_create_image_buffer(t_config *config)
{
	config->img.img = mlx_new_image(config->mlx, WIDTH, HEIGHT);
	if (!config->img.img)
	{
		printf("Error\nFailed to create image buffer\n");
		return (0);
	}
	config->img.addr = mlx_get_data_addr(config->img.img, &config->img.bpp,
			&config->img.line_len, &config->img.endian);
	if (!config->img.addr)
	{
		printf("Error\nFailed to get image data\n");
		return (0);
	}
	return (1);
}
