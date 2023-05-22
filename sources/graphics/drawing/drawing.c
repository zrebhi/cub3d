/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:51:55 by zrebhi            #+#    #+#             */
/*   Updated: 2023/05/19 15:51:55 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_pixel_color(t_graphics *graphics_data, t_dda *dda, \
		double wall_height, int x, int y);
void	draw_ray_init(t_dda *dda, t_player *player_data);
void	draw_ray(t_graphics *graphics_data, \
		t_player *player_data, t_dda *dda, int x);

void	draw_lines(t_graphics *graphics_data, t_player *player)
{
	int		x;

	mini_map(&graphics_data->map_img_data, \
	&graphics_data->parse_data->map_data, &graphics_data->player_data);
	x = 0;
	graphics_data->dda.ray = rotate_vector(player->dir, -FOV / 2);
	while (x < W_WIDTH)
	{
		graphics_data->dda.ray = rotate_vector \
		(graphics_data->dda.ray, ((double) FOV / (double) W_WIDTH));
		draw_ray(graphics_data, player, &graphics_data->dda, x);
		draw_vector (graphics_data, player->pos, \
		graphics_data->dda.hit_dist * 10, &graphics_data->dda.ray);
		x++;
	}
	mlx_put_image_to_window(graphics_data->mlx, \
	graphics_data->mlx_win, graphics_data->img_data.img, 0, 0);
	mlx_put_image_to_window(graphics_data->mlx, \
	graphics_data->mlx_win, graphics_data->map_img_data.img, 0, 0);
}

void	draw_ray(t_graphics *graphics_data, \
		t_player *player_data, t_dda *dda, int x)
{
	double		wall_height;
	int			y;
	int			color;

	draw_ray_init(dda, player_data);
	wall_height = get_wall_height(dda, graphics_data, \
	graphics_data->parse_data->map_data.map, x);
	y = 0;
	while (y <= (W_HEIGHT - wall_height) / 2 && y < W_HEIGHT)
		my_mlx_pixel_put(&graphics_data->img_data, x, y++, \
		graphics_data->parse_data->colors_data.ceiling_color);
	while (y <= (W_HEIGHT + wall_height) / 2 && y < W_HEIGHT)
	{
		color = get_pixel_color(graphics_data, dda, wall_height, x, y);
		my_mlx_pixel_put(&graphics_data->img_data, x, y, color);
		y++;
	}
	while (y < W_HEIGHT)
		my_mlx_pixel_put(&graphics_data->img_data, x, y++, \
		graphics_data->parse_data->colors_data.floor_color);
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

int	get_pixel_color(t_graphics *graphics_data, t_dda *dda, \
	double wall_height, int x, int y)
{
	t_img		texture;
	t_vectori	coordinates_in_texture;
	int			color;

	texture = wall_orientation_texture(dda, graphics_data);
	coordinates_in_texture = pixel_coordinates_in_texture \
		(wall_height, &texture, x, y, graphics_data);
	color = get_pixel_value(&texture, \
		coordinates_in_texture.x, coordinates_in_texture.y);
	return (color);
}
