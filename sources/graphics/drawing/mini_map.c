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

#include "cub3d.h"

void	draw_vector(t_graphics *graphics_data, \
		t_vectord start, double len, t_vectord *ray)
{
	t_vectord	end;
	t_vectord	diff;
	t_vectord	step;
	double		steps;

	start.x *= 10;
	start.y *= 10;
	end.x = start.x + len * ray->x / sqrt(ray->x * ray->x + ray->y * ray->y);
	end.y = start.y + len * ray->y / sqrt(ray->x * ray->x + ray->y * ray->y);
	diff.x = end.x - start.x;
	diff.y = end.y - start.y;
	steps = fmax(fabs(diff.x), fabs(diff.y));
	step.x = diff.x / steps;
	step.y = diff.y / steps;
	while (steps >= 0)
	{
		my_mlx_pixel_put(&graphics_data->map_img_data, (int)start.x + \
		(int)(step.x * steps), (int) start.y + (int)(step.y * steps), \
		0x00FF0000);
		steps--;
	}
}

void	mini_map(t_img *img, t_map *map_data, t_player *player_data)
{
	int	i;
	int	j;

	i = 0;
	while (i < (map_data->map_width * 10))
	{
		j = 0;
		while (j < (map_data->map_height * 10))
		{
			if (j == floor(player_data->pos.y * 10) \
			&& i == (int)floor(player_data->pos.x * 10))
				my_mlx_pixel_put(img, i, j, 0x55FF0000);
			else if (map_data->map[j / 10][i / 10] == '0')
				my_mlx_pixel_put(img, i, j, 0x55FFFFFF);
			else if (map_data->map[j / 10][i / 10] == '1')
				my_mlx_pixel_put(img, i, j, 0x55000000);
			j++;
		}
		i++;
	}
}
