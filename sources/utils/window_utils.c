/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:08:18 by marobert          #+#    #+#             */
/*   Updated: 2023/05/12 16:09:53 by marobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window_utils.h"

int	exit_window(t_game *game)
{
	(void)game;
	exit(0);
}

int	key_handler(int key, t_game *game)
{
	if (key == 65307)
		exit_window(game);
	else if (key == 'w')
		forward(game->player, 1, game->map);
	else if (key == 's')
		forward(game->player, -1, game->map);
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

void	init_img(t_window *window, t_map *map)
{
	window->img.img = mlx_new_image(window->mlx_ptr, W_WIDTH, W_HEIGHT);
	window->m_map.img = mlx_new_image(window->mlx_ptr, \
									map->width * 10, map->height * 10);
	if (!window->img.img || !window->m_map.img)
		exit(printf("mlx error\n"));
	window->img.addr = mlx_get_data_addr(window->img.img, \
		&window->img.bpp, &window->img.line_length, \
		&window->img.endian);
	window->m_map.addr = mlx_get_data_addr(window->m_map.img, \
		&window->m_map.bpp, &window->m_map.line_length, \
		&window->m_map.endian);
	if (!window->img.addr || !window->m_map.addr)
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
	if (!window->mlx_ptr)
		exit(printf("mlx error\n"));
	window->win_ptr = mlx_new_window(window->mlx_ptr, W_WIDTH, W_HEIGHT, TITLE);
	if (!window->win_ptr)
		exit(printf("mlx error\n"));
	game->player = init_player(map);
	game->map = map;
	game->win = window;
	init_img(window, map);
	draw_lines(game, window, game->player, game->map);
	mlx_hook(window->win_ptr, 2, 1L << 0, key_handler, game);
	mlx_hook(window->win_ptr, 17, 1L << 2, exit_window, &window);
	return (game);
}
