/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:40:22 by zrebhi            #+#    #+#             */
/*   Updated: 2023/05/16 15:40:22 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static double	get_height(t_dda *dda, t_graphics *graphics_data, char **map)
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
		dda->hit_dist = (dda->side_dist.y - dda->delta_dist.y);
	else
		dda->hit_dist = (dda->side_dist.x - dda->delta_dist.x);
	return (W_WIDTH / dda->hit_dist);
}

void	draw_ray(t_graphics *graphics_data, t_player *player, t_dda *dda, int x)
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
	height = get_height(dda, graphics_data, graphics_data->parse_data->map_data.map) / cosf((FOV / W_WIDTH) * x - (FOV / 2));
	printf("%f\n", height);
	y = 0;
	while (y <= (W_HEIGHT - height) / 2 && y < W_HEIGHT)
		my_mlx_pixel_put(&graphics_data->img_data, x, y++, 0x550000FF);
	while (y <= (W_HEIGHT + height) / 2 && y < W_HEIGHT)
		my_mlx_pixel_put(&graphics_data->img_data, x, y++, 0x5500FF00);
	while (y < W_HEIGHT)
		my_mlx_pixel_put(&graphics_data->img_data, x, y++, 0x55FF0000);
}

t_vectord	rotate(t_vectord vector, double angle)
{
	t_vectord	new;

	new.x = vector.x * cos(angle) - vector.y * sin(angle);
	new.y = vector.x * sin(angle) + vector.y * cos(angle);
	return (new);
}

void	draw_lines(t_graphics *graphics_data, t_player *player)
{
	int		i;
	t_dda	dda;

//	mini_map(&graphics_data->map_img_data, &graphics_data->parse_data->map_data, \
//	&graphics_data->player_data, graphics_data);
	i = 0;
	dda.ray = rotate(player->dir, -FOV / 2);
	while (i < W_WIDTH)
	{
		dda.ray = rotate(dda.ray, (FOV / W_WIDTH));
		draw_ray(graphics_data, player, &dda, i);
//		draw_vector(graphics_data, player->pos, dda.hit_dist * 10, &dda.ray);
		i++;
	}
	mlx_put_image_to_window(graphics_data->mlx, \
	graphics_data->mlx_win, graphics_data->img_data.img, 0, 0);
//	mlx_put_image_to_window(graphics_data->mlx, \
//	graphics_data->mlx_win, graphics_data->map_img_data.img, 0, 0);
}