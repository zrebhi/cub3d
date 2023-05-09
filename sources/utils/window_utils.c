/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:08:18 by marobert          #+#    #+#             */
/*   Updated: 2023/05/09 15:27:43 by marobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window_utils.h"

static int	fill_window(t_window *win, t_map *map, t_player *player);

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
		forward(game->player);
	else if (key == 's')
		backward(game->player);
	else if (key == 'a')
		rotate_left(game->player);
	else if (key == 'd')
		rotate_right(game->player);
	else
		printf("%c\n", key);
	fill_window(game->win, game->map, game->player);
	return (1);
}

void	put_pxl_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *) dst = color;
}

static void	draw_vector(t_window *win, t_vector position, t_vector direction)
{
	t_vector	diff;
	t_vector	step;
	double		steps;

	direction.x = position.x + (direction.x * 10);
	direction.y = position.y + (direction.y * 10);
	printf("pos : %f %f\n", position.x, position.y);
	printf("dir : %f %f\n", direction.x, direction.y);
	diff.x = direction.x - position.x;
	diff.y = direction.y - position.y;
	steps = fmax(fabs(diff.x), fabs(diff.y));
	step.x = diff.x / steps;
	step.y = diff.y / steps;
	printf("steps: %f\n", steps);
	while (steps >= 0)
	{
		if ((int)(position.x + (step.x * steps)) < W_WIDTH && \
			(int)(position.y + (step.y * steps)) < W_HEIGHT)
			put_pxl_img(&win->img, (int)position.x + (int)(step.x * steps), \
				(int)position.y + (int)(step.y * steps), 0x00FF0000);
		steps--;
	}
}


static int	fill_window(t_window *win, t_map *map, t_player *player)
{
	int	x;
	int	y;
	int	map_x;
	int	map_y;

	y = 0;
	while (y < W_HEIGHT)
	{
		map_y = y * (map->height - 1) / W_HEIGHT;
		x = 0;
		while (x < W_WIDTH)
		{
			map_x = x * (map->width - 1) / W_WIDTH;
			if (in_range(player->pos.x, x - 10, x + 10) && in_range(player->pos.y, y - 10, y + 10))
				put_pxl_img(&win->img, x, y, COL_PLAYER);
			else if ((int)ft_strlen(map->map[map_y]) - 1 <= map_x || \
				ft_strchr(" 1", map->map[map_y][map_x]))
				put_pxl_img(&win->img, x, y, COL_WALL);
			else
				put_pxl_img(&win->img, x, y, COL_EMPTY);
			x++;
		}
		y++;
	}
	draw_vector(win, player->pos, player->dir);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img.img, 0, 0);
	return (1);
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
	game->win = window;
	init_img(window);
	fill_window(game->win, game->map, game->player);
	mlx_do_key_autorepeaton(window->mlx_ptr);
//	mlx_hook(window->win_ptr, 02, 1L << 1, key_handler, &window); //TODO utiliser un tableau de bool pour avec un event keypress et keyrelease
	mlx_key_hook(window->win_ptr, key_handler, game);
	mlx_hook(window->win_ptr, 17, 1L << 2, exit_window, &window);
	return (game);
}

int	game_loop(t_game *game)
{
	mlx_loop(game->win->mlx_ptr);
	return (1);
}
