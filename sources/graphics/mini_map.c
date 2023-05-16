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

void draw_line(t_img *img, int x0, int y0, int x1, int y1, int color, char **map)
{
	int dx;
	int dy;
	int sx;
	int sy;
	int err;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	err = dx - dy;
	if (x0 < x1)
		sx = 1;
	else
		sx = -1;
	if (y0 < y1)
		sy = 1;
	else
		sy = -1;
	while (1)
	{
		my_mlx_pixel_put(img, x0, y0, color);
		if (map[y0][x0] == '1')
			break;
		if (2 * err > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (2 * err < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	mini_map(t_img *img, t_map *map_data, t_graphics *graphics_data)
{
	int i, j;

	int squareSize = 40; // Size of each square (10 by 10 pixels)

	i = 0;
	while (i < (map_data->map_width * squareSize))
	{
		j = 0;
		while (j < (map_data->map_height * squareSize) && j < 1080)
		{
			int mapX = i / squareSize;
			int mapY = j / squareSize;

			if (map_data->map[mapY][mapX] == '1')
			{
				// Draw a filled square with the desired color
				for (int dx = 0; dx < squareSize; dx++)
				{
					for (int dy = 0; dy < squareSize; dy++)
					{
						int pixelX = i + dx;
						int pixelY = j + dy;
						my_mlx_pixel_put(img, pixelX, pixelY, 0xFF000000);
					}
				}
			}
			if (map_data->map[mapY][mapX] == '0')
			{
				// Draw a filled square with a different color for the player position
				for (int dx = 0; dx < squareSize; dx++)
				{
					for (int dy = 0; dy < squareSize; dy++)
					{
						int pixelX = i + dx;
						int pixelY = j + dy;
						my_mlx_pixel_put(img, pixelX, pixelY, 0xFFFFFFFF);
					}
				}
			}
			if (i / squareSize == (int)(graphics_data->player_data.pos.x) && \
			j /squareSize == (int)(graphics_data->player_data.pos.y))
			{
				// Draw a filled square with a different color for the player position
				for (int dx = 0; dx < squareSize; dx++)
				{
					for (int dy = 0; dy < squareSize; dy++)
					{
						int pixelX = i + dx;
						int pixelY = j + dy;
						my_mlx_pixel_put(img, pixelX, pixelY, 0xFFFF0000);
					}
				}
			}
			j += squareSize;
		}
		i += squareSize;
	}

	mlx_put_image_to_window(graphics_data->mlx, graphics_data->mlx_win, graphics_data->img_data.img, 0, 0);
}
