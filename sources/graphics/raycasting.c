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
		dda->hit_dist = (dda->side_dist.x - dda->delta_dist.x);
	else
		dda->hit_dist = (dda->side_dist.y - dda->delta_dist.y);
	return (W_WIDTH / dda->hit_dist);
}

void	draw_ray_init(t_dda *dda, t_player *player_data)
{
	dda->box_map.x = floor(player_data->pos.x);
	dda->box_map.y = floor(player_data->pos.y);
	dda->delta_dist.x = 1e30;
	if (dda->ray.x != 0)
		dda->delta_dist.x = fabs(1 / dda->ray.x);
	dda->delta_dist.y = 1e30;
	if (dda->ray.y != 0)
		dda->delta_dist.y = fabs(1 / dda->ray.y);
}

void	draw_ray(t_graphics *graphics_data, t_player *player_data, t_dda *dda, int x)
{
	double	wall_height;
	int		y;
	t_vectori coordinates_in_texture;

	draw_ray_init(dda, player_data);
	wall_height = get_height(dda, graphics_data, graphics_data->parse_data->map_data.map) \
	/ (double)cosf((FOV / W_WIDTH) * x - (FOV / 2));
	y = 0;
	while (y <= (W_HEIGHT - wall_height) / 2 && y < W_HEIGHT) {
		my_mlx_pixel_put(&graphics_data->img_data, x, y++, \
		graphics_data->parse_data->colors_data.ceiling_color);
	}
	while (y <= (W_HEIGHT + wall_height) / 2 && y < W_HEIGHT) {
		coordinates_in_texture = pixel_coordinates_in_texture(wall_height, graphics_data->textures[0], x, y);
		my_mlx_pixel_put(&graphics_data->img_data, x, y, \
		get_pixel_value(&graphics_data->textures[0], coordinates_in_texture.x, coordinates_in_texture.y));
		y++;
	}
	while (y < W_HEIGHT) {
		my_mlx_pixel_put(&graphics_data->img_data, x, y++, \
		graphics_data->parse_data->colors_data.floor_color);
	}
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

	mini_map(&graphics_data->map_img_data, &graphics_data->parse_data->map_data, \
	&graphics_data->player_data, graphics_data);
	i = 0;
	dda.ray = rotate(player->dir, -FOV / 2);
	while (i < W_WIDTH)
	{
		dda.ray = rotate(dda.ray, ((double) FOV / (double) W_WIDTH));
		draw_ray(graphics_data, player, &dda, i);
		draw_line(floor(player->pos.x * 10), floor(player->pos.y * 10), dda.box_map.x * 10, dda.box_map.y * 10, &graphics_data->map_img_data, 0xFF0000);
//				draw_vector(graphics_data, player->pos, dda.hit_dist * 10, &dda.ray);
		i++;
	}
	mlx_put_image_to_window(graphics_data->mlx, graphics_data->mlx_win, graphics_data->img_data.img, 0, 0);
	mlx_put_image_to_window(graphics_data->mlx, graphics_data->mlx_win, graphics_data->map_img_data.img, 0, 0);
}
