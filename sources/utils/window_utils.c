/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:08:18 by marobert          #+#    #+#             */
/*   Updated: 2023/05/11 10:52:27 by marobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window_utils.h"

int	exit_window(t_game *game)
{
	(void)game;
//	mlx_destroy_image(game->win->mlx_ptr, game->win->img.img);
//	mlx_destroy_window(game->win->mlx_ptr, game->win->win_ptr);
	exit(0);
}

int	key_handler(int key, t_game *game)
{
	if (key == 65307)
		exit_window(game);
	else if (key == 'w')
		forward(game->player, 1);
	else if (key == 's')
		forward(game->player, -1);
	else if (key == 'a')
		rotate_left(game->player);
	else if (key == 'd')
		rotate_right(game->player);
	else
		printf("%c\n", key);
	draw_lines(game, game->win, game->player, game->map);
	return (1);
}

void	put_pxl_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *) dst = color;
}

void	init_img(t_window *window)
{
	window->img.img = mlx_new_image(window->mlx_ptr, W_WIDTH, W_HEIGHT);
	window->img.addr = mlx_get_data_addr(window->img.img, \
		&window->img.bpp, &window->img.line_length, \
		&window->img.endian);
	if (!window->img.addr)
		exit(1);
}

t_game	*init_game(t_map *map)
{
	t_window	*window;
	t_game		*game;

	game = malloc(sizeof(t_game));
	window = malloc(sizeof(t_window));
	if (!game || !window)
		exit(1);
	window->mlx_ptr = mlx_init();
	window->win_ptr = mlx_new_window(window->mlx_ptr, W_WIDTH, W_HEIGHT, TITLE);
	game->player = init_player(map);
	game->map = map;
	game->map->floor = 0x797c7d;
	game->map->ceil = 0x38a5c7;
	game->win = window;
	init_img(window);
	draw_lines(game, window, game->player, game->map);
	mlx_key_hook(window->win_ptr, key_handler, game);
	mlx_hook(window->win_ptr, 17, 1L << 2, exit_window, &window);
	return (game);
}
