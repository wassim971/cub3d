/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wassim <wassim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 19:11:35 by wassim            #+#    #+#             */
/*   Updated: 2026/01/13 19:11:39 by wassim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/**
 * close_game - Ferme proprement le jeu
 */
int	close_game(t_config *config)
{
	free_config(config);
	if (config->img.img)
		mlx_destroy_image(config->mlx, config->img.img);
	if (config->tex_north.img)
		mlx_destroy_image(config->mlx, config->tex_north.img);
	if (config->tex_south.img)
		mlx_destroy_image(config->mlx, config->tex_south.img);
	if (config->tex_west.img)
		mlx_destroy_image(config->mlx, config->tex_west.img);
	if (config->tex_east.img)
		mlx_destroy_image(config->mlx, config->tex_east.img);
	if (config->win)
		mlx_destroy_window(config->mlx, config->win);
	if (config->mlx)
	{
		mlx_destroy_display(config->mlx);
		free(config->mlx);
	}
	exit(0);
	return (0);
}

/**
 * key_press - Gestion des touches pressées
 */
int	key_press(int keycode, t_config *config)
{
	if (keycode == KEY_ESC)
		close_game(config);
	else if (keycode == KEY_W)
		config->keys.w = 1;
	else if (keycode == KEY_S)
		config->keys.s = 1;
	else if (keycode == KEY_A)
		config->keys.a = 1;
	else if (keycode == KEY_D)
		config->keys.d = 1;
	else if (keycode == KEY_LEFT)
		config->keys.left = 1;
	else if (keycode == KEY_RIGHT)
		config->keys.right = 1;
	return (0);
}

/**
 * key_release - Gestion des touches relâchées
 */
int	key_release(int keycode, t_config *config)
{
	if (keycode == KEY_W)
		config->keys.w = 0;
	else if (keycode == KEY_S)
		config->keys.s = 0;
	else if (keycode == KEY_A)
		config->keys.a = 0;
	else if (keycode == KEY_D)
		config->keys.d = 0;
	else if (keycode == KEY_LEFT)
		config->keys.left = 0;
	else if (keycode == KEY_RIGHT)
		config->keys.right = 0;
	return (0);
}

/**
 * game_loop - Boucle principale du jeu
 */
int	game_loop(t_config *config)
{
	if (config->keys.w)
		move_forward(config);
	if (config->keys.s)
		move_backward(config);
	if (config->keys.a)
		move_left(config);
	if (config->keys.d)
		move_right(config);
	if (config->keys.left)
		rotate_left(config);
	if (config->keys.right)
		rotate_right(config);
	render_frame(config);
	return (0);
}

/**
 * setup_hooks - Configure tous les hooks MLX
 */
void	setup_hooks(t_config *config)
{
	mlx_hook(config->win, 2, 1L << 0, key_press, config);
	mlx_hook(config->win, 3, 1L << 1, key_release, config);
	mlx_hook(config->win, 17, 0, close_game, config);
	mlx_loop_hook(config->mlx, game_loop, config);
}
