/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:59:58 by marobert          #+#    #+#             */
/*   Updated: 2023/05/04 14:24:55 by marobert         ###   ########.fr       */
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
}

void	rotate_left(t_player *player)
{
	double	new_x;
	double	new_y;

	new_x = cos(-ROTATE) * player->dir.x - sin(-ROTATE) * player->dir.y;
	new_y = sin(-ROTATE) * player->dir.x + cos(-ROTATE) * player->dir.y;
	player->dir.x = new_x;
	player->dir.y = new_y;
}

void	forward(t_player *player)
{
	player->pos.x = player->pos.x - player->dir.x;
	player->pos.y = player->pos.y - player->dir.y;
}

void	backward(t_player *player)
{
	player->pos.x = player->pos.x + player->dir.x;
	player->pos.y = player->pos.y + player->dir.y;
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
				player->pos.x = ((double)(x * W_WIDTH) / (double)map->width);
				player->pos.y = ((double)(y * W_HEIGHT) / (double)map->height);
				printf("\nplayer : %f %f\n", player->pos.x, player->pos.y);
				if (map->map[y][x] == 'N')
				{
					player->dir.x = 0;
					player->dir.y = SPEED;
				}
				else if (map->map[y][x] == 'S')
				{
					player->dir.x = 0;
					player->dir.y = -SPEED;
				}
				else if (map->map[y][x] == 'E')
				{
					player->dir.x = SPEED;
					player->dir.y = 0;
				}
				else if (map->map[y][x] == 'W')
				{
					player->dir.x = -SPEED;
					player->dir.y = 0;
				}
			}
			x++;
		}
		y++;
	}
	return (player);
}