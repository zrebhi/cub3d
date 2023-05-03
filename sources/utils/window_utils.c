/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:08:18 by marobert          #+#    #+#             */
/*   Updated: 2023/05/03 22:11:57 by marobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window_utils.h"

static int fill_window(t_window *win, t_map *map, t_player *player);

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
		game->player->pos_y += STEP_Y;
	else if (key == 's')
		game->player->pos_y -= STEP_Y;
	else
		printf("%c\n", key);
//	fill_window(game->win, game->map, game->player);
	return (1);
}

void put_pxl_img(t_img *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *) dst = color;
}

static int fill_window(t_window *win, t_map *map, t_player *player)
{
	int		x;
	int		y;
	size_t	line_len;

	y = 0;
	while (y < W_HEIGHT)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			line_len = ft_strlen(map->map[y * (map->height - 1) / W_HEIGHT]) - 1;
			if (in_range(player->pos_x, x - 10, x + 10) && in_range(player->pos_y, y - 10, y + 10)) // player.pos_x is for map,
				put_pxl_img(&win->img, x, y, 0x00FF00BB);
			else if ((int)line_len <= x * (map->width) / W_WIDTH || \
				ft_strchr(" 1", map->map[y * (map->height - 1) / W_HEIGHT] \
				[x * (map->width - 1) / W_WIDTH]))
				put_pxl_img(&win->img, x, y, 0x00000000);
			else
				put_pxl_img(&win->img, x, y, 0x00FFFFFF);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img.img, 0, 0);
	return (1);
}

void init_img(t_window *window)
{
	window->img.img = mlx_new_image(window->mlx_ptr, W_WIDTH, W_HEIGHT);
	window->img.addr = mlx_get_data_addr(window->img.img, \
		&window->img.bpp, &window->img.line_length, \
		&window->img.endian);
}

t_player	*init_player(t_map *map)
{
	t_player	*player;
	int			x;
	int			y;
	int			line_len;

	printf("init player\n");
	player = malloc(sizeof(t_player));
	if (!player)
		exit(1);
	y = 0;
	while (y < map->height)
	{
		line_len = (int)ft_strlen(map->map[y]);
		x = 0;
		while (x < map->width)
		{
			if (x < line_len && ft_isalpha(map->map[y][x]))
			{
				printf("\nmap: %d %d", x, y);
				player->pos_x = ((double)(x * W_WIDTH) / (double)map->width);
				player->pos_y = ((double)(y * W_HEIGHT) / (double)map->height);
				printf("\nplayer : %f %f\n", player->pos_x, player->pos_y);
				if (map->map[y][x] == 'N')
				{
					player->dir_x = 0;
					player->dir_y = 1;
				}
				else if (map->map[y][x] == 'S')
				{
					player->dir_x = 0;
					player->dir_y = -1;
				}
				else if (map->map[y][x] == 'E')
				{
					player->dir_x = 1;
					player->dir_y = 0;
				}
				else if (map->map[y][x] == 'W')
				{
					player->dir_x = -1;
					player->dir_y = 0;
				}
			}
			x++;
		}
		y++;
	}
	return (player);
}

t_game *init_game(t_map *map)
{
	t_window	window;
	t_game		*game;

	game = malloc(sizeof(t_game));
	if (!game)
		exit(1);
	window.mlx_ptr = mlx_init();
	window.win_ptr = mlx_new_window(window.mlx_ptr, W_WIDTH, W_HEIGHT, TITLE);
	game->player = init_player(map);
	game->win = &window;
	game->map = map;
	init_img(&window);
	fill_window(game->win, game->map, game->player);
	mlx_key_hook(window.win_ptr, key_handler, game);
	mlx_hook(window.win_ptr, 17, 1L << 2, exit_window, &window);
	return (game);
}

int	game_loop(t_game *game)
{
	mlx_loop(game->win->mlx_ptr);
	return (1);
}