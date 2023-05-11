/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:31:19 by marobert          #+#    #+#             */
/*   Updated: 2023/05/11 15:34:06 by marobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window_utils.h"

static void	draw_vector(t_window *win, t_vectord position, t_vectord direction)
{
	t_vectord	diff;
	t_vectord	step;
	double		steps;

	position.x *= 10;
	position.y *= 10;
	direction.x = position.x + (direction.x * 25);
	direction.y = position.y + (direction.y * 25);
	diff.x = direction.x - position.x;
	diff.y = direction.y - position.y;
	steps = fmax(fabs(diff.x), fabs(diff.y));
	step.x = diff.x / steps;
	step.y = diff.y / steps;
	while (steps >= 0)
	{
		if (in_range((int)(position.x + (step.x * steps)), 0, W_WIDTH) && \
			in_range((int)(position.y + (step.y * steps)), 0, W_HEIGHT))
			put_pxl_img(&win->img, (int)position.x + (int)(step.x * steps), \
				(int)position.y + (int)(step.y * steps), 0x00FF0000);
		steps--;
	}
}

void	draw_fov_map(t_window *win, t_player *player)
{
	int			i;
	t_vectord	ray;

	i = 0;
	ray = rotate(player->dir, -FOV / 2);
	while (i < W_WIDTH)
	{
		ray = rotate(ray, (FOV / W_WIDTH));
		draw_vector(win, player->pos, ray);
		i++;
	}
}

void	draw_map(t_window *win, t_player *player, t_map *map)
{
	int			i;
	int			j;

	i = 0;
	while (i < (map->width * 10))
	{
		j = 0;
		while (j < (map->height * 10))
		{
			if (i == (int)floor(player->pos.x * 10) && \
				j == (int)floor(player->pos.y * 10))
				put_pxl_img(&win->img, i, j, 0x55FF0000);
			else if (ft_isalpha(map->map[j * map->height / (map->height * 10)] \
					[i * (map->width) / (map->width * 10)]) || \
					map->map[j * map->height / (map->height * 10)] \
					[i * (map->width) / (map->width * 10)] == '0')
				put_pxl_img(&win->img, i, j, 0x55FFFFFF);
			else if (map->map[j * map->height / (map->height * 10)] \
					[i * (map->width) / (map->width * 10)] == '1')
				put_pxl_img(&win->img, i, j, 0x55000000);
			j++;
		}
		i++;
	}
	draw_fov_map(win, player);
}
