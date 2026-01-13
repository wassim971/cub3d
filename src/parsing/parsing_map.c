/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:54:53 by ainthana          #+#    #+#             */
/*   Updated: 2025/12/15 12:59:23 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	fill_map_row(char *row, char *line, int width)
{
	int	x;
	int	len;

	x = 0;
	len = ft_strlen(line);
	while (x < width)
	{
		if (x < len && line[x] != '\n' && line[x] != '\r')
		{
			if (line[x] == '\t')
				row[x] = ' ';
			else
				row[x] = line[x];
		}
		else
			row[x] = ' ';
		x++;
	}
	row[width] = '\0';
}

static void	find_player(char c, int x, int y, t_config *config)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		config->player.x = x + 0.5;
		config->player.y = y + 0.5;
		config->player.dir = c;
	}
}

// Modifié : Retourne int et s'arrête à la première ligne vide
static int	init_map(t_config *config, char **lines, int *height, int *width)
{
	int	len;

	*height = 0;
	*width = 0;
	while (lines[*height] && !is_empty_line(lines[*height]))
	{
		len = ft_strlen(lines[*height]);
		if (len > *width)
			*width = len;
		(*height)++;
	}
	config->map.grid = malloc(sizeof(char *) * (*height + 1));
	if (!config->map.grid)
		return (error_msg("Error : allocation failed for map"));
	config->map.height = *height;
	config->map.width = *width;
	return (1);
}

static void	fill_line(char *dest, char *src, t_config *config, int y)
{
	int	x;

	x = 0;
	while (x < (int)ft_strlen(src))
	{
		find_player(src[x], x, y, config);
		x++;
	}
	fill_map_row(dest, src, config->map.width);
}

int	parse_map(char **lines, t_config *config)
{
	int	y;
	int	h;
	int	w;

	y = 0;
	while (lines[y] && !is_empty_line(lines[y]))
		y++;
	while (lines[y])
	{
		if (!is_empty_line(lines[y++]))
			return (error_msg("Error : Empty line inside or after map"));
	}
	if (!init_map(config, lines, &h, &w))
		return (0);
	y = 0;
	while (y < h)
	{
		config->map.grid[y] = malloc(sizeof(char) * (w + 1));
		if (!config->map.grid[y])
			return (error_msg("Error : allocation failed for map row"));
		fill_line(config->map.grid[y], lines[y], config, y);
		y++;
	}
	config->map.grid[h] = NULL;
	return (1);
}
