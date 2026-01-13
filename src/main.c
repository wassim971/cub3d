/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wassim <wassim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 11:56:07 by ainthana          #+#    #+#             */
/*   Updated: 2026/01/13 19:43:37 by wassim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


static void	init_config(t_config *cfg)
{
	cfg->mlx = NULL;
	cfg->win = NULL;
	cfg->img.img = NULL;
	cfg->textures.north = NULL;
	cfg->textures.south = NULL;
	cfg->textures.west = NULL;
	cfg->textures.east = NULL;
	cfg->tex_north.img = NULL;
	cfg->tex_south.img = NULL;
	cfg->tex_west.img = NULL;
	cfg->tex_east.img = NULL;
	cfg->floor.r = -1;
	cfg->floor.g = -1;
	cfg->floor.b = -1;
	cfg->ceiling.r = -1;
	cfg->ceiling.g = -1;
	cfg->ceiling.b = -1;
	cfg->map.grid = NULL;
	cfg->map.width = 0;
	cfg->map.height = 0;
	cfg->player.x = -1;
	cfg->player.y = -1;
	cfg->player.dir = 0;
	cfg->player.angle = 0;
	init_keys(cfg);
}


void	init_keys(t_config *config)
{
	config->keys.w = 0;
	config->keys.s = 0;
	config->keys.a = 0;
	config->keys.d = 0;
	config->keys.left = 0;
	config->keys.right = 0;
}


void	init_player_angle(t_config *config)
{
	if (config->player.dir == 'N')
		config->player.angle = 3 * M_PI / 2;
	else if (config->player.dir == 'S')
		config->player.angle = M_PI / 2;
	else if (config->player.dir == 'E')
		config->player.angle = 0;
	else if (config->player.dir == 'W')
		config->player.angle = M_PI;
}

void	free_config(t_config *cfg)
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

int	main(int argc, char **argv)
{
	t_config	config;
	char		**tab;

	if (argc != 2)
		print_error("Usage: ./cub3d <map.cub>");
	init_config(&config);
	if (!check_file(argv[1]))
		exit(1);
	tab = read_cub_file(argv[1]);
	parse_cub(tab, &config);
	free_split(tab);
	if (!init_mlx(&config))
	{
		free_config(&config);
		exit(1);
	}
	init_player_angle(&config);
	setup_hooks(&config);
	render_frame(&config);
	mlx_loop(config.mlx);
	return (0);
}
