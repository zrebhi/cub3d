/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:08:18 by marobert          #+#    #+#             */
/*   Updated: 2023/05/03 15:56:00 by marobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window_utils.h"

int	exit_window(void *a)
{
	(void) a;

	exit(0);
}

int	key_handler(int key, t_window *window)
{
	if (key == 65307)
		exit_window(window);
	return (1);
}

void put_pxl_img(t_data *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *) dst = color;
}

static int fill_window(t_window *win, t_cub *cub)
{
	int		x;
	int		y;
	size_t	line_len;

	y = 0;
	while (y < W_HEIGHT)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			line_len = ft_strlen(cub->map[y * (cub->m_height - 1) / W_HEIGHT]) - 1;
			if ((int)line_len <= x * (cub->m_mwidth) / W_WIDTH || \
				ft_strchr(" 1", cub->map[y * (cub->m_height - 1) / W_HEIGHT] \
				[x * (cub->m_mwidth - 1) / W_WIDTH]))
				put_pxl_img(&win->img, x, y, 0x00000000);
			else if (ft_isalpha(cub->map[y * (cub->m_height - 1) / W_HEIGHT] \
					[x * (cub->m_mwidth - 1) / W_WIDTH]))
				put_pxl_img(&win->img, x, y, 0x00FF00BB);
			else
				put_pxl_img(&win->img, x, y, 0x00FFFFFF);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img.img, 0, 0);
	return (1);
}

void init_img(t_window *window)
{
	window->img.img = mlx_new_image(window->mlx_ptr, W_WIDTH, W_HEIGHT);
	window->img.addr = mlx_get_data_addr(window->img.img, \
		&window->img.bpp, &window->img.line_length, \
		&window->img.endian);
}

int create_window(t_cub *cub)
{
	t_window window;

	window.mlx_ptr = mlx_init();
	window.win_ptr = mlx_new_window(window.mlx_ptr, W_WIDTH, W_HEIGHT, TITLE);
	init_img(&window);
	fill_window(&window, cub);
/*	mlx_mouse_hook(window.win_ptr, mouse_handler, &window);
	mlx_do_key_autorepeaton(window.mlx_ptr);
	mlx_put_image_to_window(window.mlx_ptr, window.win_ptr, \
		window.img.img, 0, 0);*/
	mlx_key_hook(window.win_ptr, key_handler, &window);
	mlx_hook(window.win_ptr, 17, 1L << 2, exit_window, &window);
	mlx_loop(window.mlx_ptr);
	return (1);
}