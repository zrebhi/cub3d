/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:31:19 by marobert          #+#    #+#             */
/*   Updated: 2023/05/11 16:09:25 by marobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window_utils.h"

void	draw_vector(t_game *game, t_vectord start, double len, t_vectord *ray)
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
		if (in_range((int)(start.x + (step.x * steps)), \
				0, game->map->width * 10) && \
			in_range((int)(start.y + (step.y * steps)), \
				0, game->map->height * 10))
			put_pxl_img(&game->win->m_map, (int)start.x + (int)(step.x * \
				steps), (int) start.y + (int)(step.y * steps), 0x00FF0000);
		steps--;
	}
}

void	draw_map(t_img *img, t_player *player, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < (map->width * 10))
	{
		j = 0;
		while (j < (map->height * 10))
		{
			if (i == (int)floor(player->pos.x * 10) && \
				j == (int)floor(player->pos.y * 10))
				put_pxl_img(img, i, j, 0x55FF0000);
			else if (ft_isalpha(map->map[j * map->height / (map->height * 10)] \
					[i * (map->width) / (map->width * 10)]) || \
					map->map[j * map->height / (map->height * 10)] \
					[i * (map->width) / (map->width * 10)] == '0')
				put_pxl_img(img, i, j, 0x55FFFFFF);
			else if (map->map[j * map->height / (map->height * 10)] \
					[i * (map->width) / (map->width * 10)] == '1')
				put_pxl_img(img, i, j, 0x55000000);
			j++;
		}
		i++;
	}
}
