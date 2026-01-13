/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:09:51 by ainthana          #+#    #+#             */
/*   Updated: 2025/12/10 15:23:55 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_chars(t_config *config)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < config->map.height)
	{
		x = 0;
		while (x < config->map.width)
		{
			c = config->map.grid[y][x];
			if (c != '0' && c != '1' && c != ' '
				&& c != 'N' && c != 'S' && c != 'E' && c != 'W')
				return (error_msg("Invalid character in map"));
			x++;
		}
		y++;
	}
	return (1);
}

int	check_all_elements_present(t_config *config)
{
	if (!config->textures.north || !config->textures.south
		|| !config->textures.west || !config->textures.east)
		return (error_msg("Error : one or more textures are missing"));
	if (config->floor.r == -1 || config->ceiling.r == -1)
		return (error_msg("Error : floor or ceiling color is missing"));
	return (1);
}

int	check_player(t_config *config)
{
	int		y;
	int		x;
	int		count;
	char	c;

	y = 0;
	count = 0;
	while (y < config->map.height)
	{
		x = 0;
		while (x < config->map.width)
		{
			c = config->map.grid[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				count++;
			x++;
		}
		y++;
	}
	if (count != 1)
		return (error_msg("Error : Wrong number of players"));
	return (1);
}

int	is_valid_map(t_config *config)
{
	if (!check_chars(config))
		return (0);
	if (!check_player(config))
		return (0);
	if (!check_floodfill(config))
		return (0);
	return (1);
}
