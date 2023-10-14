/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:59:06 by zrebhi            #+#    #+#             */
/*   Updated: 2023/05/16 16:10:16 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	graphics_init(t_graphics *graphics_data)
{
	graphics_data->mlx = mlx_init();
	if (!graphics_data->mlx)
		return (1);
	graphics_data->mlx_win = mlx_new_window \
	(graphics_data->mlx, W_WIDTH, W_HEIGHT, "Cub3D!");
	get_textures(graphics_data, &graphics_data->parse_data->colors_data);
	init_player(&graphics_data->parse_data->map_data.map, \
	&graphics_data->player_data);
	graphics_data->img_data.img = mlx_new_image \
	(graphics_data->mlx, W_WIDTH, W_HEIGHT);
	graphics_data->img_data.addr = mlx_get_data_addr \
	(graphics_data->img_data.img, &graphics_data->img_data.bits_per_pixel, \
	&graphics_data->img_data.line_length, &graphics_data->img_data.endian);
	graphics_data->map_img_data.img = mlx_new_image \
	(graphics_data->mlx, \
	graphics_data->parse_data->map_data.map_width * 10, \
	graphics_data->parse_data->map_data.map_height * 10);
	graphics_data->map_img_data.addr = mlx_get_data_addr \
	(graphics_data->map_img_data.img, \
	&graphics_data->map_img_data.bits_per_pixel, \
	&graphics_data->map_img_data.line_length, \
	&graphics_data->map_img_data.endian);
	return (0);
}

void	my_mlx_pixel_put(t_img *img_data, int x, int y, int color)
{
	char	*dst;

	dst = img_data->addr + \
	(y * img_data->line_length + x * (img_data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

int	render(t_graphics *graphics_data)
{
	if (graphics_data->keys[KEY_W])
		move_forward(&graphics_data->player_data, .5, \
		graphics_data->parse_data->map_data.map);
	if (graphics_data->keys[KEY_S])
		move_forward(&graphics_data->player_data, -.5, \
		graphics_data->parse_data->map_data.map);
	if (graphics_data->keys[KEY_A])
		move_aside(&graphics_data->player_data, -.5, \
		graphics_data->parse_data->map_data.map);
	if (graphics_data->keys[KEY_D])
		move_aside(&graphics_data->player_data, .5, \
		graphics_data->parse_data->map_data.map);
	if (graphics_data->keys[KEY_ARROW_L] || graphics_data->keys[KEY_Q])
		rotate_side(&graphics_data->player_data, -.5);
	if (graphics_data->keys[KEY_ARROW_R] || graphics_data->keys[KEY_E])
		rotate_side(&graphics_data->player_data, .5);
	draw_lines(graphics_data, &graphics_data->player_data);
	return (1);
}

int	graphics(t_graphics *graphics_data)
{
	graphics_init(graphics_data);
	draw_lines(graphics_data, &graphics_data->player_data);
	mlx_hook(graphics_data->mlx_win, 2, 1L << 0, key_pressed, graphics_data);
	mlx_hook(graphics_data->mlx_win, 3, 1L << 1, key_released, graphics_data);
	mlx_hook(graphics_data->mlx_win, 17, 1L << 2, exit_window, graphics_data);
	mlx_loop_hook(graphics_data->mlx, render, graphics_data);
	mlx_loop(graphics_data->mlx);
	return (0);
}
