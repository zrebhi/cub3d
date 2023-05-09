/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:19:50 by marobert          #+#    #+#             */
/*   Updated: 2023/05/09 18:51:27 by marobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window_utils.h"

static double	get_ray_x(t_vector *ray, t_vector *side_dist, t_player *player, \
						t_vector *box_map)
{
	double	tmp;

	tmp = 999999;
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

	tmp = 999999;
	if (ray->x != 0)
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
	while (game->map->map[(int)box_map->y][(int)box_map->x] != '0')
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
		return (W_HEIGHT / ((delta_dist->y - side_dist.y) / 100));
	return (W_HEIGHT / ((delta_dist->x - side_dist.x) / 100));
}

void	draw_ray(t_game *game, t_player *player, t_vector *ray, int x)
{
	t_vector	box_map;
	double		height;
	t_vector	delta_dist;
	int			y;

	box_map.x = floor(player->pos.x / W_WIDTH * game->map->width);
	box_map.y = floor(player->pos.y / W_HEIGHT * game->map->height);
	delta_dist.x = 999999;
	if (ray->x != 0)
		delta_dist.x = fabs(1 / ray->x);
	delta_dist.y = 999999;
	if (ray->y != 0)
		delta_dist.y = fabs(1 / ray->y);
	height = get_height(&delta_dist, &box_map, ray, game);
	y = -1;
	while (++y < W_HEIGHT)
	{
		if (y < (W_HEIGHT - height) / 2)
			put_pxl_img(&game->win->img, x, y, game->map->ceil);
		else if (y > (W_HEIGHT + height) / 2)
			put_pxl_img(&game->win->img, x, y, game->map->floor);
		else
			put_pxl_img(&game->win->img, x, y, 0x000000FF);
	}
}

void	draw_lines(t_game *game, t_window *win, t_player *player, t_map *map)
{
	int			i;
	t_vector	ray;

	player->cam.x = 0;
	player->cam.y = 0.66;
	i = 0;
	while (i < W_WIDTH)
	{
		ray.x = player->dir.y + player->cam.y * 2 * i / W_WIDTH - 1;
		ray.y = player->dir.y + player->cam.x * 2 * i / W_WIDTH - 1;
		draw_ray(game, player, &ray, i);
		i++;
	}
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img.img, 0, 0);
}
