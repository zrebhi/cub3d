/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_borders_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:28:07 by zrebhi            #+#    #+#             */
/*   Updated: 2023/05/03 12:28:07 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	map_is_open(t_parsing *data, int x, int y)
{
	if (y == 0 || y == data->map_height - 1)
		return (1);
	if (x == 0 || x == data->map_width - 1)
		return (1);
	if (data->map[y + 1][x] == ' ' || data->map[y - 1][x] == ' ' \
	|| data->map[y][x + 1] == ' ' || data->map[y][x - 1] == ' ')
		return (1);
	return (0);
}

int	check_closed_map(t_parsing *data)
{
	int	x;
	int	y;

	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (data->map[y][x] == '0' && map_is_open(data, x, y))
				return (1);
		}
	}
	return (0);
}
