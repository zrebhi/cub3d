/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:34:48 by zrebhi            #+#    #+#             */
/*   Updated: 2023/05/12 19:34:48 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

void	init_player(char **map, t_player *player_data)
{
	char	dir;

	find_player(map, player_data);
	dir = map[(int)(player_data->pos.y)][(int)(player_data->pos.x)];
	player_data->dir.x = 0;
	player_data->dir.y = 0;
	if (dir == 'N')
		player_data->dir.y = 1;
	if (dir == 'S')
		player_data->dir.y = -1;
	if (dir == 'E')
		player_data->dir.x = 1;
	if (dir == 'W')
		player_data->dir.x = -1;
}

void	mini_map(t_img *img, t_map *map_data, t_player *player_data)
{
	int	i;
	int	j;

	i = 0;
	while (i < (map_data->map_width * 50))
	{
		j = 0;
		while (j < (map_data->map_height * 50))
		{
			if (j == (int)floor(player_data->pos.y * 50) && i == (int)floor(player_data->pos.x * 50)) {
				printf("%d\n", j);
				printf("%d\n", i);
				my_mlx_pixel_put(img, i, j, 0xFFFF0000);
			}
			else if (map_data->map[j / 50][i / 50] == '0')
				my_mlx_pixel_put(img, i, j, 0x55FFFFFF);
			else if (map_data->map[j / 50][i / 50] == '1')
				my_mlx_pixel_put(img, i, j, 0x55000000);
			j++;
		}
		i++;
	}
}
