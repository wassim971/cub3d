/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:39:44 by ainthana          #+#    #+#             */
/*   Updated: 2025/12/15 13:13:44 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_texture(char *str)
{
	if (!str)
		return (0);
	if ((!ft_strncmp(str, "NO", 2) || !ft_strncmp(str, "SO", 2)
			|| !ft_strncmp(str, "WE", 2) || !ft_strncmp(str, "EA", 2))
		&& (str[2] == ' ' || str[2] == '\t' || str[2] == '\0'))
		return (1);
	return (0);
}

int	is_color(char *str)
{
	if (!str)
		return (0);
	if ((!ft_strncmp(str, "F", 1) || !ft_strncmp(str, "C", 1))
		&& (str[1] == ' ' || str[1] == '\t' || str[1] == '\0'))
		return (1);
	return (0);
}

int	is_map_start(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (0);
	if (is_texture(&line[i]) || is_color(&line[i]))
		return (0);
	if (line[i] == '0' || line[i] == '1' || line[i] == 'N'
		|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		return (1);
	return (0);
}

int	is_valid_rgb(char **rgb)
{
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (0);
	remove_newline(rgb[2]);
	if (!ft_isnumber(rgb[0]) || !ft_isnumber(rgb[1]) || !ft_isnumber(rgb[2]))
		return (0);
	return (1);
}

char	*get_join_color(char **tokens)
{
	char	*res;
	int		len;
	int		i;
	int		j;
	int		k;

	len = 0;
	i = 1;
	while (tokens[i])
		len += ft_strlen(tokens[i++]);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 1;
	k = 0;
	while (tokens[i])
	{
		j = 0;
		while (tokens[i][j])
			res[k++] = tokens[i][j++];
		i++;
	}
	res[k] = '\0';
	return (res);
}
