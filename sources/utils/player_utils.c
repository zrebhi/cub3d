/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:59:58 by marobert          #+#    #+#             */
/*   Updated: 2023/06/05 16:51:53 by marobert         ###   ########.fr       */
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
void	forward(t_player *player, int dir, t_map *map)
{
	double	tmp;

	tmp = player->pos.x + ((player->dir.x / 10) * dir);
	if (map->map[(int)player->pos.y][(int)tmp] != '1')
		player->pos.x = tmp;
	tmp = player->pos.y + ((player->dir.y / 10) * dir);
	if (map->map[(int)tmp][(int)player->pos.x] != '1')
		player->pos.y = tmp;
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
		while (x < map->map_width)
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
