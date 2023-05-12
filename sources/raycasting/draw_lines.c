/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:19:50 by marobert          #+#    #+#             */
/*   Updated: 2023/05/12 18:15:40 by marobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window_utils.h"

static int	get_ray_x(t_player *player, t_dda *dda)
{
	double	tmp;

	tmp = 1e30;
	if (dda->ray.x != 0)
		tmp = fabs(1 / (dda->ray.x));
	if (dda->ray.x < 0)
	{
		dda->side_dist.x = (player->pos.x - dda->box_map.x) * tmp;
		return (-1);
	}
	else
	{
		dda->side_dist.x = (dda->box_map.x + 1.0 - player->pos.x) * tmp;
		return (1);
	}
}

static int	get_ray_y(t_player *player, t_dda *dda)

{
	double	tmp;

	tmp = 1e30;
	if (dda->ray.y != 0)
		tmp = fabs(1 / (dda->ray.y));
	if (dda->ray.y < 0)
	{
		dda->side_dist.y = (player->pos.y - dda->box_map.y) * tmp;
		return (-1);
	}
	else
	{
		dda->side_dist.y = (dda->box_map.y + 1.0 - player->pos.y) * tmp;
		return (1);
	}
}

static double	get_height(t_dda *dda, t_game *game)
{
	dda->step.x = get_ray_x(game->player, dda);
	dda->step.y = get_ray_y(game->player, dda);
	dda->side = 0;
	while (in_range(dda->box_map.x, 0, game->map->width) && \
		in_range(dda->box_map.y, 0, game->map->height) && \
		game->map->map[dda->box_map.y][dda->box_map.x] != '1')
	{
		if (dda->side_dist.x < dda->side_dist.y)
		{
			dda->side_dist.x += dda->delta_dist.x;
			dda->box_map.x += dda->step.x;
			dda->side = 0;
		}
		else
		{
			dda->side_dist.y += dda->delta_dist.y;
			dda->box_map.y += dda->step.y;
			dda->side = 1;
		}
	}
	dda->hit_dist = (dda->side_dist.x - dda->delta_dist.x);
	if (dda->side)
		dda->hit_dist = (dda->side_dist.y - dda->delta_dist.y);
	return (W_WIDTH / dda->hit_dist);
}

void	draw_ray(t_game *game, t_player *player, t_dda *dda, int x)
{
	double	height;
	int		y;

	dda->box_map.x = floor(player->pos.x);
	dda->box_map.y = floor(player->pos.y);
	dda->delta_dist.x = 1e30;
	if (dda->ray.x != 0)
		dda->delta_dist.x = fabs(1 / dda->ray.x);
	dda->delta_dist.y = 1e30;
	if (dda->ray.y != 0)
		dda->delta_dist.y = fabs(1 / dda->ray.y);
	height = get_height(dda, game) / cosf((FOV / W_WIDTH) * x - (FOV / 2));
	y = 0;
	while (y <= (W_HEIGHT - height) / 2 && y < W_HEIGHT)
		put_pxl_img(&game->win->img, x, y++, game->map->ceil);
	while (y <= (W_HEIGHT + height) / 2 && y < W_HEIGHT)
		put_pxl_img(&game->win->img, x, y++, get_color_side(dda));
	while (y < W_HEIGHT)
		put_pxl_img(&game->win->img, x, y++, game->map->floor);
}

void	draw_lines(t_game *game, t_window *win, t_player *player, t_map *map)
{
	int		i;
	t_dda	dda;

	draw_map(&win->m_map, player, map);
	i = 0;
	dda.ray = rotate(player->dir, -FOV / 2);
	while (i < W_WIDTH)
	{
		dda.ray = rotate(dda.ray, (FOV / W_WIDTH));
		draw_ray(game, player, &dda, i);
		draw_vector(game, player->pos, dda.hit_dist * 10, &dda.ray);
		i++;
	}
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img.img, 0, 0);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->m_map.img, 0, 0);
}
