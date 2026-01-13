/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:40:34 by ainthana          #+#    #+#             */
/*   Updated: 2025/12/15 13:18:48 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	set_texture(char **dest, char **tokens)
{
	if (*dest)
		return (error_msg("Error : texture defined multiple times"));
	remove_newline(tokens[1]);
	*dest = ft_strdup(tokens[1]);
	return (1);
}

int	parse_texture(char **tokens, t_config *config)
{
	if (!tokens[1] || tokens[2])
		return (error_msg("Error : texture config requires exactly one path"));
	if (!ft_strncmp(tokens[0], "NO", 3))
		return (set_texture(&config->textures.north, tokens));
	else if (!ft_strncmp(tokens[0], "SO", 3))
		return (set_texture(&config->textures.south, tokens));
	else if (!ft_strncmp(tokens[0], "WE", 3))
		return (set_texture(&config->textures.west, tokens));
	else if (!ft_strncmp(tokens[0], "EA", 3))
		return (set_texture(&config->textures.east, tokens));
	return (1);
}

int	assign_color(char *str, t_color *color)
{
	char	**rgb;

	if (!check_virg(str))
		return (error_msg("Error : Invalid RGB format"));
	rgb = ft_split(str, ',');
	if (!rgb)
		return (error_msg("Error: ft_split allocation failed"));
	if (!is_valid_rgb(rgb))
	{
		free_split(rgb);
		return (error_msg("Error : invalid RGB values"));
	}
	color->r = ft_atoi(rgb[0]);
	color->g = ft_atoi(rgb[1]);
	color->b = ft_atoi(rgb[2]);
	free_split(rgb);
	if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255
		|| color->b < 0 || color->b > 255)
		return (error_msg("Error : RGB out of range"));
	return (1);
}

int	parse_color(char **tokens, t_config *config)
{
	char	*color_str;
	int		res;

	color_str = get_join_color(tokens);
	if (!color_str)
		return (error_msg("Error : color config is missing"));
	res = 0;
	if (!ft_strncmp(tokens[0], "F", 2))
	{
		if (config->floor.r != -1)
			res = error_msg("Error : floor color defined multiple times");
		else
			res = assign_color(color_str, &config->floor);
	}
	else if (!ft_strncmp(tokens[0], "C", 2))
	{
		if (config->ceiling.r != -1)
			res = error_msg("Error : ceiling color defined multiple times");
		else
			res = assign_color(color_str, &config->ceiling);
	}
	free(color_str);
	return (res);
}

int	parse_config_line(char *line, t_config *config)
{
	char	**tokens;
	int		ret;

	replace_tabs_with_spaces(line);
	tokens = ft_split(line, ' ');
	if (!tokens)
		return (1);
	if (!tokens[0])
	{
		free_split(tokens);
		return (1);
	}
	ret = 1;
	if (is_texture(tokens[0]))
		ret = parse_texture(tokens, config);
	else if (is_color(tokens[0]))
		ret = parse_color(tokens, config);
	else
		ret = error_msg("Error : unknown configuration line");
	free_split(tokens);
	return (ret);
}
