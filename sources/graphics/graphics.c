/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:59:06 by zrebhi            #+#    #+#             */
/*   Updated: 2023/06/01 14:29:23 by marobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	graphics_init(t_graphics *graphics_data)
{
	graphics_data->mlx = mlx_init();
	if (!graphics_data->mlx)
		return (1);
	graphics_data->mlx_win = mlx_new_window \
	(graphics_data->mlx, 1920, 1080, "Hello world!");
	graphics_data->img_data.img = mlx_new_image \
	(graphics_data->mlx, 1920, 1080);
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
	get_textures(graphics_data, &graphics_data->parse_data->colors_data);
	init_player(&graphics_data->parse_data->map_data.map, \
	&graphics_data->player_data);
	return (0);
}

void	my_mlx_pixel_put(t_img *img_data, int x, int y, int color)
{
	char	*dst;

	dst = img_data->addr + \
	(y * img_data->line_length + x * (img_data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

int	exit_window(t_graphics *graphics_data)
{
	int	i;

	i = -1;
	while (++i < 4)
		mlx_destroy_image(graphics_data->mlx, graphics_data->textures[i].img);
	mlx_destroy_image(graphics_data->mlx, graphics_data->img_data.img);
	mlx_destroy_image(graphics_data->mlx, graphics_data->map_img_data.img);
	mlx_destroy_window(graphics_data->mlx, graphics_data->mlx_win);
	mlx_destroy_display(graphics_data->mlx);
	free(graphics_data->mlx);
	close_fds(&graphics_data->parse_data->colors_data, 4);
	ft_free(graphics_data->parse_data->m_free);
	exit (0);
}

int	key_handler(int key, t_graphics *graphics_data)
{
	if (key == 65307)
		exit_window(graphics_data);
	else if (key == W)
		move_forward(&graphics_data->player_data, 1, \
		graphics_data->parse_data->map_data.map);
	else if (key == S)
		move_forward(&graphics_data->player_data, -1, \
		graphics_data->parse_data->map_data.map);
	else if (key == A)
		move_aside(&graphics_data->player_data, -1, \
		graphics_data->parse_data->map_data.map);
	else if (key == D)
		move_aside(&graphics_data->player_data, 1, \
		graphics_data->parse_data->map_data.map);
	else if (key == ARROW_L || key == Q)
		rotate_side(&graphics_data->player_data, -1);
	else if (key == ARROW_R || key == E)
		rotate_side(&graphics_data->player_data, 1);
	else
		printf("%d\n", key);
	draw_lines(graphics_data, &graphics_data->player_data);
	return (1);
}

int	graphics(t_graphics *graphics_data)
{
	graphics_init(graphics_data);
	draw_lines(graphics_data, &graphics_data->player_data);
	mlx_hook(graphics_data->mlx_win, 2, 1L << 0, key_handler, graphics_data);
	mlx_hook(graphics_data->mlx_win, 17, 1L << 2, exit_window, graphics_data);
	mlx_loop(graphics_data->mlx);
	return (0);
}
