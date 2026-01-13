/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:10:12 by ainthana          #+#    #+#             */
/*   Updated: 2025/12/15 13:18:15 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_virg(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		return (0);
	return (1);
}

void	remove_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' || str[i] == '\r')
		{
			str[i] = '\0';
			return ;
		}
		i++;
	}
}

void	replace_tabs_with_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			line[i] = ' ';
		i++;
	}
}
