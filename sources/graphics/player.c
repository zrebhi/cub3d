/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:51:10 by zrebhi            #+#    #+#             */
/*   Updated: 2023/05/15 15:51:10 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_player(char **map, t_player *player_data)
{
	int	x;
	int	y;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (is_player(map[y][x]))
			{
				player_data->pos.x = x;
				player_data->pos.y = y;
				break ;
			}
		}
	}
}

void	init_player(char ***map, t_player *player_data)
{
	char	dir;

	find_player((*map), player_data);
	dir = (*map)[(int)(player_data->pos.y)][(int)(player_data->pos.x)];
	player_data->dir.x = 0;
	player_data->dir.y = 0;
	if (dir == 'N')
		player_data->dir.y = -1;
	if (dir == 'S')
		player_data->dir.y = 1;
	if (dir == 'E')
		player_data->dir.x = -1;
	if (dir == 'W')
		player_data->dir.x = 1;
	(*map)[(int)(player_data->pos.y)][(int)(player_data->pos.x)] = '0';
}

void	move_forward(t_player *player, int dir, char **map)
{
	double	tmp;

	tmp = player->pos.y + ((player->dir.y / 10) * dir);
	if (map[(int)tmp][(int)player->pos.x] != '1')
		player->pos.y = tmp;
	tmp = player->pos.x + ((player->dir.x / 10) * dir);
	if (map[(int)player->pos.y][(int)tmp] != '1')
		player->pos.x = tmp;
}

void move_aside(t_player *player, int dir, char **map)
{
	double tmp;
	double lateralDirX;
	double lateralDirY;

	lateralDirX = -player->dir.y;
	lateralDirY = player->dir.x;
	tmp = player->pos.x + ((lateralDirX / 10) * dir);
	if (map[(int)player->pos.y][(int)tmp] != '1')
		player->pos.x = tmp;
	tmp = player->pos.y + ((lateralDirY / 10) * dir);
	if (map[(int)tmp][(int)player->pos.x] != '1')
		player->pos.y = tmp;
}

void	rotate_side(t_player *player, int dir)
{
	double	new_x;
	double	new_y;

	new_x = cos(dir * 0.05) * player->dir.x - sin(dir * 0.05) * player->dir.y;
	new_y = sin(dir * 0.05) * player->dir.x + cos(dir * 0.05) * player->dir.y;
	player->dir.x = new_x;
	player->dir.y = new_y;
}