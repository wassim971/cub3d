/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 11:56:48 by ainthana          #+#    #+#             */
/*   Updated: 2025/12/15 13:18:20 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include "../minilibx-linux/mlx.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "../get_next_line/get_next_line.h"


// Couleurs ANSI pour printf

# define RESET       "\033[0m"
# define BOLD        "\033[1m"

# define RED         "\033[31m"
# define GREEN       "\033[32m"
# define YELLOW      "\033[33m"
# define BLUE        "\033[34m"
# define MAGENTA     "\033[35m"
# define CYAN        "\033[36m"
# define WHITE       "\033[37m"

// keys

# define KEY_W        119
# define KEY_A        97
# define KEY_S        115
# define KEY_D        100
# define KEY_ESC      65307
# define KEY_LEFT     65361
# define KEY_RIGHT    65363


// Stuctures
typedef struct	s_textures {
	char	*north;
	char	*south;
	char	*east;
	char	*west;
}	t_textures;

typedef struct	s_color {
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct	s_map {
	char	**grid;
	int		width;
	int		height;		
}	t_map;

typedef struct s_player {
	double	x;
	double	y;
	char	dir; //point cardinaux
}	t_player;

typedef struct s_config {
    t_textures  textures;
    t_color     floor;
    t_color     ceiling;
    t_map       map;
    t_player    player;
} t_config;

// functions

void	print_error(const char *msg);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
char	**ft_split(char const *s, char c);
void	free_split(char **split);
int		ft_isnumber(char *str);
int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);
void	remove_newline(char *str);
void	free_config(t_config *cfg);
int		error_msg(char *msg);
int		check_virg(char *str);
int		is_valid_rgb(char **rgb);
char	*get_join_color(char **tokens);
void	replace_tabs_with_spaces(char *line);

int		is_empty_line(char *line);
int		is_texture(char *str);
int		is_color(char *str);
int		is_map_start(char *line);

int		check_file(char *filename);
int		check_player(t_config *config);
int		check_chars(t_config *config);
int		open_cub_file(char *file);
char 	**read_cub_file(char *filename);

void	parse_cub(char **tab, t_config *config);
int		parse_config_line(char *line, t_config *config);
int		parse_texture(char **tokens, t_config *config);
int		parse_texture2(char **tokens, t_config *config);
int		parse_color(char **tokens, t_config *config);
int		assign_color(char *str, t_color *color);
int		check_all_elements_present(t_config *config);
int		check_floodfill(t_config *config);

int		is_valid_map(t_config *config);
int		is_map_start(char *line);

int		parse_map(char **lines, t_config *config);

#endif