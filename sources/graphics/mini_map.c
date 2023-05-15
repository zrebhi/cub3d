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

void	draw_mini_map(t_img *img, t_map *map_data)
{
	int	i;
	int	j;

	i = 0;
	while (i < (map_data->map_width * 10))
	{
		j = 0;
		while (j < (map_data->map_height * 10))
		{
			if (map_data->map[j * map_data->map_height / (map_data->map_height * 10)] \
			[i * (map_data->map_width) / (map_data->map_width * 10)] == '0')
				my_mlx_pixel_put(img, i, j, 0x55FFFFFF);
			else if (map_data->map[j * map_data->map_height / (map_data->map_height * 10)] \
					[i * (map_data->map_width) / (map_data->map_width * 10)] == '1')
				my_mlx_pixel_put(img, i, j, 0x55000000);
			j++;
		}
		i++;
	}
}
