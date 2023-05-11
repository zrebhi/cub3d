/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:59:58 by marobert          #+#    #+#             */
/*   Updated: 2023/05/11 11:15:59 by marobert         ###   ########.fr       */
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

/*
 * Move the player forward or backward
 * @param player a pointer to a player struct
 * @param dir -1 to move backward, 1 to move forward
 */
void	forward(t_player *player, int dir)
{
	player->pos.x = player->pos.x + ((player->dir.x / 10) * dir);
	player->pos.y = player->pos.y + ((player->dir.y / 10) * dir);
}

static void	set_dir(t_player *player, char pos)
{
	player->dir.x = 0;
	player->dir.y = 0;
	if (pos == 'N')
		player->dir.y = -SPEED;
	else if (pos == 'S')
		player->dir.y = SPEED;
	else if (pos == 'E')
		player->dir.x = SPEED;
	else if (pos == 'W')
		player->dir.x = -SPEED;
}

t_player	*init_player(t_map *map)
{
	t_player	*player;
	int			x;
	int			y;

	player = malloc(sizeof(t_player));
	if (!player)
		exit(1);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (x < (int)ft_strlen(map->map[y]) && ft_isalpha(map->map[y][x]))
			{
				player->pos.x = x + .5;
				player->pos.y = y + .5;
				printf("\nplayer : %f %f\n", player->pos.x, player->pos.y);
				set_dir(player, map->map[y][x]);
			}
			x++;
		}
		y++;
	}
	return (player);
}
