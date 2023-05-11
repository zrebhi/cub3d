/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:19:50 by marobert          #+#    #+#             */
/*   Updated: 2023/05/11 11:16:22 by marobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window_utils.h"

static int	get_ray_x(t_vectord *ray, t_vectord *side_dist, \
						t_player *player, t_vectori *box_map)
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

static int	get_ray_y(t_vectord *ray, t_vectord *side_dist, \
						t_player *player, t_vectori *box_map)
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

static double	get_height(t_vectord *delta_dist, t_vectori *box_map, \
								t_vectord *ray, t_game *game)
{
	int			side;
	t_vectord	side_dist;
	t_vectori	step;

	step.x = get_ray_x(ray, &side_dist, game->player, box_map);
	step.y = get_ray_y(ray, &side_dist, game->player, box_map);
	side = 0;
	while (in_range((int)box_map->x, 1, game->map->width) && \
		in_range((int)box_map->y, 1, game->map->height) && \
		game->map->map[(int)box_map->y][(int)box_map->x] != '1')
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

void	draw_ray(t_game *game, t_player *player, t_vectord *ray, int x)
{
	t_vectori	box_map;
	double		height;
	t_vectord	delta_dist;
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
		put_pxl_img(&game->win->img, x, y, 0x4aa162);
	while (++y < W_HEIGHT && y < W_HEIGHT)
		put_pxl_img(&game->win->img, x, y, game->map->floor);
}

void	draw_lines(t_game *game, t_window *win, t_player *player, t_map *map)
{
	int			i;
	t_vectord	ray;

	i = 0;
	ray = rotate(player->dir, -FOV / 2);
	while (i < W_WIDTH)
	{
		ray = rotate(ray, (FOV / W_WIDTH));
		draw_ray(game, player, &ray, i);
		i++;
	}
	draw_map(win, player, map);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img.img, 0, 0);
}
