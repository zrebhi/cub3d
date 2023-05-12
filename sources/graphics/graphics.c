/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:59:06 by zrebhi            #+#    #+#             */
/*   Updated: 2023/05/12 18:59:06 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	graphics_init(t_graphics *graphics_data)
{
	graphics_data->mlx = mlx_init();
	graphics_data->mlx_win = mlx_new_window(graphics_data->mlx, \
	1920, 1080, "Hello world!");
	graphics_data->img_data.img = mlx_new_image(graphics_data->mlx, \
	1920, 1080);
	graphics_data->img_data.addr = mlx_get_data_addr \
	(graphics_data->img_data.img, &graphics_data->img_data.bits_per_pixel, \
	&graphics_data->img_data.line_length, &graphics_data->img_data.endian);
	return (0);
}

void	my_mlx_pixel_put(t_img *img_data, int x, int y, int color)
{
	char	*dst;

	dst = img_data->addr + \
	(y * img_data->line_length + x * (img_data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw(t_graphics *graphics_data)
{
	int	x;
	int	y;

	x = -1;
	while (++x < 1920)
	{
		y = -1;
		while (++y < 1080)
			my_mlx_pixel_put(&graphics_data->img_data, x, y, 0x00FFFFFF);
	}
}

int	graphics(t_graphics *graphics_data)
{
	graphics_init(graphics_data);
	draw(graphics_data);
	mlx_put_image_to_window(graphics_data->mlx, graphics_data->mlx_win, \
	graphics_data->img_data.img, 0, 0);
	mlx_loop(graphics_data->mlx);
	return (0);
}
