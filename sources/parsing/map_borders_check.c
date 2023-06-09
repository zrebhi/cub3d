/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_borders_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:28:07 by zrebhi            #+#    #+#             */
/*   Updated: 2023/05/12 15:52:18 by marobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_is_open(t_map *map_data, int x, int y)
{
	if (y == 0 || y == map_data->map_height - 1)
		return (1);
	if (x == 0 || x == map_data->map_width - 1)
		return (1);
	if (map_data->map[y + 1][x] == ' ' || map_data->map[y - 1][x] == ' ' \
	|| map_data->map[y][x + 1] == ' ' || map_data->map[y][x - 1] == ' ')
		return (1);
	return (0);
}

int	check_closed_map(t_map *map_data)
{
	int	x;
	int	y;

	y = -1;
	while (map_data->map[++y])
	{
		x = -1;
		while (map_data->map[y][++x])
		{
			if ((map_data->map[y][x] == '0' || is_player(map_data->map[y][x])) \
			&& map_is_open(map_data, x, y))
				return (1);
		}
	}
	return (0);
}
