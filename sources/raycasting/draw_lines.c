/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:19:50 by marobert          #+#    #+#             */
/*   Updated: 2023/05/10 16:17:46 by marobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window_utils.h"

static double	get_ray_x(t_vector *ray, t_vector *side_dist, t_player *player, \
						t_vector *box_map)
{
	double	tmp;

	tmp = 1e30;
	if (ray->x != 0)
		tmp = fabs(1 / (ray->x));
	if (ray->x < 0)
	{
		side_dist->x = (player->pos.x - box_map->x) * tmp;
		return (-1);
	}
	else
	{
		side_dist->x = (box_map->x + 1.0 - player->pos.x) * tmp;
		return (1);
	}
}

static double	get_ray_y(t_vector *ray, t_vector *side_dist, t_player *player, \
						t_vector *box_map)
{
	double	tmp;

	tmp = 1e30;
	if (ray->y != 0)
		tmp = fabs(1 / (ray->y));
	if (ray->y < 0)
	{
		side_dist->y = (player->pos.y - box_map->y) * tmp;
		return (-1);
	}
	else
	{
		side_dist->y = (box_map->y + 1.0 - player->pos.y) * tmp;
		return (1);
	}
}

static double	get_height(t_vector *delta_dist, t_vector *box_map, \
								t_vector *ray, t_game *game)
{
	int			side;
	t_vector	side_dist;
	t_vector	step;

	step.x = get_ray_x(ray, &side_dist, game->player, box_map);
	step.y = get_ray_y(ray, &side_dist, game->player, box_map);
	while (in_range((int)box_map->x, 1, game->map->width) && in_range((int)box_map->y, \
	1, game->map->height) && game->map->map[(int)box_map->y][(int)box_map->x] != '0')
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta_dist->x;
			box_map->x += step.x;
			side = 0;
		}
		else
		{
			side_dist.y += delta_dist->y;
			box_map->y += step.y;
			side = 1;
		}
	}
	if (side)
		return (W_HEIGHT / ((side_dist.y - delta_dist->y)));
	return (W_HEIGHT / ((side_dist.x - delta_dist->x)));
}

void	draw_ray(t_game *game, t_player *player, t_vector *ray, int x)
{
	t_vector	box_map;
	double		height;
	t_vector	delta_dist;
	int			y;

	box_map.x = floor(player->pos.x);
	box_map.y = floor(player->pos.y);
	delta_dist.x = 1e30;
	if (ray->x != 0)
		delta_dist.x = fabs(1 / ray->x);
	delta_dist.y = 1e30;
	if (ray->y != 0)
		delta_dist.y = fabs(1 / ray->y);
	height = get_height(&delta_dist, &box_map, ray, game);
	y = -1;
	while (++y <= (W_HEIGHT - height) / 2 && y < W_HEIGHT)
			put_pxl_img(&game->win->img, x, y, game->map->ceil);
	while (++y <= (W_HEIGHT + height) / 2 && y < W_HEIGHT)
			put_pxl_img(&game->win->img, x, y, 0x000000FF);
	while (++y < W_HEIGHT && y < W_HEIGHT)
			put_pxl_img(&game->win->img, x, y, game->map->floor);
}

void	draw_lines(t_game *game, t_window *win, t_player *player, t_map *map)
{
	int			i;
	int			j;
	t_vector	ray;

	i = 0;
	while (i < W_WIDTH)
	{
		ray.x = player->dir.y + player->cam.y * (2 * i / W_WIDTH - 1);
		ray.y = player->dir.y + player->cam.x * (2 * i / W_WIDTH - 1);
		draw_ray(game, player, &ray, i);
		i++;
	}
	i = 0;
	while (i < 150)
	{
		j = 0;
		while (j < 150)
		{
			if (i == (int)floor(player->pos.x * 150 / map->width) && j == (int)floor(player->pos.y * 150 / map->height))
				put_pxl_img(&win->img, i, j, 0x55FF0000);
			else if (map->map[j * map->height / 150][i * (map->width - 1) / 150] == '1')
				put_pxl_img(&win->img, i, j, 0x55000000);
			else
				put_pxl_img(&win->img, i, j, 0x55FFFFFF);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img.img, 0, 0);
}


/*

 map	|	map_max
 win	|	win_max

 * */