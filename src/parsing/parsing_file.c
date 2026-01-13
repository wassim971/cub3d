/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:39:05 by ainthana          #+#    #+#             */
/*   Updated: 2025/12/10 15:34:49 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_file(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(filename + len - 4, ".cub", 4) != 0)
	{
		print_error("error : fichier invalide: extension .cub requise");
		return (0);
	}
	return (1);
}

int	open_cub_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(RED"Error: cannot open .cub file");
		exit(1);
	}
	return (fd);
}

int	count_lines(char *filename)
{
	int		fd;
	char	*line;
	int		count;

	count = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error: Cannot open .cub file for counting");
		exit(1);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

char	**read_cub_file(char *filename)
{
	int		total_lines;
	char	**tab;
	int		fd;
	char	*line;
	int		i;

	total_lines = count_lines(filename);
	tab = malloc(sizeof(char *) * (total_lines + 1));
	if (!tab)
		print_error("Error: Allocation failed for main tab.");
	fd = open_cub_file(filename);
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		tab[i] = line;
		i++;
		line = get_next_line(fd);
	}
	tab[i] = NULL;
	close(fd);
	return (tab);
}
