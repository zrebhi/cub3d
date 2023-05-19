/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zak <zak@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:40:22 by zrebhi            #+#    #+#             */
/*   Updated: 2023/05/18 19:18:46 by zak              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_ray_x(t_player *player, t_dda *dda);
void	get_ray_y(t_player *player, t_dda *dda);
void	get_hit_dist(t_dda *dda, t_graphics *graphics_data, char **map);

t_vectord	rotate_vector(t_vectord vector, double angle)
{
	t_vectord	new;

	new.x = vector.x * cos(angle) - vector.y * sin(angle);
	new.y = vector.x * sin(angle) + vector.y * cos(angle);
	return (new);
}

double	get_wall_height(t_dda *dda, t_graphics *graphics_data, \
								char **map, int x)
{
	double	wall_height;
	double	fisheye_fix;

	get_hit_dist(dda, graphics_data, map);
	fisheye_fix = 1 / ((double)cosf((FOV / W_WIDTH) * x - (FOV / 2)));
	wall_height = dda->hit_dist * fisheye_fix;

	return (wall_height);
}

void	get_hit_dist(t_dda *dda, t_graphics *graphics_data, char **map)
{
	get_ray_x(&graphics_data->player_data, dda);
	get_ray_y(&graphics_data->player_data, dda);
	dda->side = 0;
	while (map[dda->box_map.y][dda->box_map.x] != '1')
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
	if (!dda->side)
		dda->hit_dist = (dda->side_dist.x - dda->delta_dist.x);
	else
		dda->hit_dist = (dda->side_dist.y - dda->delta_dist.y);
}

void	get_ray_x(t_player *player, t_dda *dda)
{
	double	tmp;

	tmp = 1e30;
	if (dda->ray.x != 0)
		tmp = fabs(1 / (dda->ray.x));
	if (dda->ray.x < 0)
	{
		dda->side_dist.x = (player->pos.x - dda->box_map.x) * tmp;
		dda->step.x = -1;
	}
	else
	{
		dda->side_dist.x = (dda->box_map.x + 1.0 - player->pos.x) * tmp;
		dda->step.x = 1;
	}
}

void	get_ray_y(t_player *player, t_dda *dda)
{
	double	tmp;

	tmp = 1e30;
	if (dda->ray.y != 0)
		tmp = fabs(1 / (dda->ray.y));
	if (dda->ray.y < 0)
	{
		dda->side_dist.y = (player->pos.y - dda->box_map.y) * tmp;
		dda->step.y = -1;
	}
	else
	{
		dda->side_dist.y = (dda->box_map.y + 1.0 - player->pos.y) * tmp;
		dda->step.y = 1;
	}
}
