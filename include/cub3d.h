/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wassim <wassim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:23:33 by wassim            #+#    #+#             */
/*   Updated: 2026/01/13 19:26:13 by wassim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include "../minilibx-linux/mlx.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include "../get_next_line/get_next_line.h"

/*===== CONSTANTES =====*/

/* Dimensions de la fenêtre */
# define WIDTH 1920
# define HEIGHT 1080

/* Touches clavier */
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

/* Paramètres de jeu */
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05
# define FOV 1.0471975512  // 60 degrés en radians
# define M_PI 3.14159265358979323846

/* Couleurs ANSI pour printf */
# define RESET "\033[0m"
# define BOLD "\033[1m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"

/*===== STRUCTURES =====*/

/* Structure pour les textures */
typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

/* Structure pour l'image de rendu */
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

/* Structure pour les chemins de textures */
typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
}	t_textures;

/* Structure pour les couleurs RGB */
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

/* Structure pour la carte */
typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

/* Structure pour le joueur */
typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
	char	dir;
}	t_player;

/* Structure pour les touches */
typedef struct s_keys
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	left;
	int	right;
}	t_keys;

/* Structure pour un rayon */
typedef struct s_ray
{
	double		dir_x;
	double		dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			draw_start;
	int			draw_end;
	double		wall_x;
	t_texture	*texture;
}	t_ray;

/* Structure principale de configuration */
typedef struct s_config
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_textures	textures;
	t_texture	tex_north;
	t_texture	tex_south;
	t_texture	tex_west;
	t_texture	tex_east;
	t_color		floor;
	t_color		ceiling;
	t_map		map;
	t_player	player;
	t_keys		keys;
}	t_config;

/*===== PROTOTYPES =====*/

/* Parsing */
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
char	**read_cub_file(char *filename);
void	parse_cub(char **tab, t_config *config);
int		parse_config_line(char *line, t_config *config);
int		parse_texture(char **tokens, t_config *config);
int		parse_color(char **tokens, t_config *config);
int		assign_color(char *str, t_color *color);
int		check_all_elements_present(t_config *config);
int		check_floodfill(t_config *config);
int		is_valid_map(t_config *config);
int		parse_map(char **lines, t_config *config);

/* Initialisation */
int		init_mlx(t_config *config);
void	init_player_angle(t_config *config);
void	init_keys(t_config *config);

/* Raycasting */
void	cast_ray(t_config *config, int x, t_ray *ray);

/* Rendu */
int		render_frame(t_config *config);

/* Mouvement */
void	move_forward(t_config *config);
void	move_backward(t_config *config);
void	move_left(t_config *config);
void	move_right(t_config *config);
void	rotate_left(t_config *config);
void	rotate_right(t_config *config);

/* Hooks */
int		close_game(t_config *config);
int		key_press(int keycode, t_config *config);
int		key_release(int keycode, t_config *config);
int		game_loop(t_config *config);
void	setup_hooks(t_config *config);

#endif
