/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:09:41 by wassim            #+#    #+#             */
/*   Updated: 2026/01/19 13:00:51 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_wall(t_config *config, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_y >= config->map.height || map_x < 0
		|| map_x >= config->map.width)
		return (1);
	if (config->map.grid[map_y][map_x] == '1')
		return (1);
	return (0);
}

int	can_move(t_config *config, double new_x, double new_y)
{
	double	margin;

	margin = 0.2;
	if (is_wall(config, new_x, new_y))
		return (0);
	if (is_wall(config, new_x + margin, new_y))
		return (0);
	if (is_wall(config, new_x - margin, new_y))
		return (0);
	if (is_wall(config, new_x, new_y + margin))
		return (0);
	if (is_wall(config, new_x, new_y - margin))
		return (0);
	return (1);
}

void	rotate_left(t_config *config)
{
	config->player.angle -= ROT_SPEED;
	if (config->player.angle < 0)
		config->player.angle += 2 * M_PI;
}

void	rotate_right(t_config *config)
{
	config->player.angle += ROT_SPEED;
	if (config->player.angle >= 2 * M_PI)
		config->player.angle -= 2 * M_PI;
}
