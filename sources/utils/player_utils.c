/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:59:58 by marobert          #+#    #+#             */
/*   Updated: 2023/05/10 12:54:14 by marobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player_utils.h"

void	rotate_right(t_player *player)
{
	double	new_x;
	double	new_y;

	new_x = cos(ROTATE) * player->dir.x - sin(ROTATE) * player->dir.y;
	new_y = sin(ROTATE) * player->dir.x + cos(ROTATE) * player->dir.y;
	player->dir.x = new_x;
	player->dir.y = new_y;
	new_x = cos(ROTATE) * player->cam.x - sin(ROTATE) * player->cam.y;
	new_y = sin(ROTATE) * player->cam.x + cos(ROTATE) * player->cam.y;
	player->cam.x = new_x;
	player->cam.y = new_y;
}

void	rotate_left(t_player *player)
{
	double	new_x;
	double	new_y;

	new_x = cos(-ROTATE) * player->dir.x - sin(-ROTATE) * player->dir.y;
	new_y = sin(-ROTATE) * player->dir.x + cos(-ROTATE) * player->dir.y;
	player->dir.x = new_x;
	player->dir.y = new_y;
	new_x = cos(-ROTATE) * player->cam.x - sin(-ROTATE) * player->cam.y;
	new_y = sin(-ROTATE) * player->cam.x + cos(-ROTATE) * player->cam.y;
	player->cam.x = new_x;
	player->cam.y = new_y;
}

void	forward(t_player *player)
{
	player->pos.x = player->pos.x - (player->dir.x / 10);
	player->pos.y = player->pos.y - (player->dir.y / 10);
}

void	backward(t_player *player)
{
	player->pos.x = player->pos.x + (player->dir.x / 10);
	player->pos.y = player->pos.y + (player->dir.y / 10);
}

t_player	*init_player(t_map *map)
{
	t_player	*player;
	int			x;
	int			y;

	printf("\ninit player\n");
	player = malloc(sizeof(t_player));
	if (!player)
		exit(1);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (x < ft_strlen(map->map[y]) && ft_isalpha(map->map[y][x]))
			{
				printf("\nmap: %d %d", x, y);
				player->pos.x = x + .5;
				player->pos.y = y + .5;
				printf("\nplayer : %f %f\n", player->pos.x, player->pos.y);
				if (map->map[y][x] == 'N')
				{
					player->dir.x = 0;
					player->dir.y = SPEED;
					player->cam.x = -0.66;
					player->cam.y = 0;
				}
				else if (map->map[y][x] == 'S')
				{
					player->dir.x = 0;
					player->dir.y = -SPEED;
					player->cam.x = 0.66;
					player->cam.y = 0;
				}
				else if (map->map[y][x] == 'E')
				{
					player->dir.x = SPEED;
					player->dir.y = 0;
					player->cam.x = 0;
					player->cam.y = -0.66;
				}
				else if (map->map[y][x] == 'W')
				{
					player->dir.x = -SPEED;
					player->dir.y = 0;
					player->cam.x = 0;
					player->cam.y = 0.66;
				}
			}
			x++;
		}
		y++;
	}
	return (player);
}
