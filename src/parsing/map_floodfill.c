/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_floodfill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:11:13 by ainthana          #+#    #+#             */
/*   Updated: 2025/12/15 12:05:34 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	flood_fill(char **tab, t_map *map, int x, int y)
{
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return (0);
	if (tab[y][x] == ' ')
		return (0);
	if (tab[y][x] == '1' || tab[y][x] == 'v')
		return (1);
	tab[y][x] = 'v';
	if (!flood_fill(tab, map, x + 1, y))
		return (0);
	if (!flood_fill(tab, map, x - 1, y))
		return (0);
	if (!flood_fill(tab, map, x, y + 1))
		return (0);
	if (!flood_fill(tab, map, x, y - 1))
		return (0);
	return (1);
}

static void	free_map_copy(char **copy, int height)
{
	int	i;

	if (!copy)
		return ;
	i = 0;
	while (i < height)
	{
		if (copy[i])
			free(copy[i]);
		i++;
	}
	free(copy);
}

static char	**duplicate_map(t_config *config)
{
	char	**copy;
	int		y;

	copy = malloc(sizeof(char *) * (config->map.height + 1));
	if (!copy)
		return (NULL);
	y = 0;
	while (y < config->map.height)
	{
		copy[y] = ft_strdup(config->map.grid[y]);
		if (!copy[y])
		{
			free_map_copy(copy, y);
			return (NULL);
		}
		y++;
	}
	copy[y] = NULL;
	return (copy);
}

int	check_floodfill(t_config *config)
{
	char	**copy;
	int		result;

	copy = duplicate_map(config);
	if (!copy)
		return (error_msg("Error : allocation failed for map validation"));
	result = flood_fill(copy, &config->map,
			(int)config->player.x, (int)config->player.y);
	free_map_copy(copy, config->map.height);
	if (!result)
		return (error_msg("Error : map is not closed"));
	return (1);
}
