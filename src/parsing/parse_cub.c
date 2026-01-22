/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:49:40 by ainthana          #+#    #+#             */
/*   Updated: 2026/01/21 16:20:02 by wbaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	free_configz(t_config *cfg)
{
	int	y;

	if (cfg->textures.north)
		free(cfg->textures.north);
	if (cfg->textures.south)
		free(cfg->textures.south);
	if (cfg->textures.west)
		free(cfg->textures.west);
	if (cfg->textures.east)
		free(cfg->textures.east);
	if (cfg->map.grid)
	{
		y = 0;
		while (y < cfg->map.height)
		{
			free(cfg->map.grid[y]);
			y++;
		}
		free(cfg->map.grid);
	}
}

static void	free_parsing(char **tab, t_config *config, char *msg)
{
	free_split(tab);
	free_configz(config);
	if (msg)
		printf("Error : %s\n", msg);
	exit(1);
}

static int	parse_configurations(char **tab, t_config *config)
{
	int	i;

	i = 0;
	while (tab[i] && !is_map_start(tab[i]))
	{
		if (!is_empty_line(tab[i]))
		{
			if (!parse_config_line(tab[i], config))
				return (-1);
		}
		i++;
	}
	return (i);
}

void	parse_cub(char **tab, t_config *config)
{
	int	i;

	if (!tab || !tab[0])
		free_parsing(tab, config, "No map found in .cub file");
	i = parse_configurations(tab, config);
	if (i == -1 || !check_all_elements_present(config))
		free_parsing(tab, config, NULL);
	if (!tab[i])
		free_parsing(tab, config, "Map not found after configuration");
	if (!parse_map(&tab[i], config))
		free_parsing(tab, config, NULL);
	if (!is_valid_map(config))
		free_parsing(tab, config, NULL);
}
