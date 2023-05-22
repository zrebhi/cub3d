/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_pixel.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:11:48 by zrebhi            #+#    #+#             */
/*   Updated: 2023/05/19 15:11:48 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_tex_x(t_dda *dda, int x, int y, t_img *texture, t_player *player_data);
double	get_wallX(t_dda *dda,  t_player *player_data, int x, int y);

int		get_pixel_value(t_img *img, int tex_x, int tex_y)
{
	char	*ptr;
	int		value;

	ptr = img->addr + (tex_y * img->line_length) + (tex_x << 2);
	value = (*(int *)ptr);
	return (value);
}

t_vectori	pixel_coordinates_in_texture(double wall_height, t_img *texture, \
			int x, int y, t_graphics *graphics_data)
{
	t_vectori coordinates;

	coordinates.y = y * 256 - W_HEIGHT * 128 + wall_height * 128;
	coordinates.y = ((coordinates.y * texture->height) / wall_height) / 256;
	coordinates.x = get_tex_x(&graphics_data->dda, x, y, texture, &graphics_data->player_data);

	return (coordinates);
}

int	get_tex_x(t_dda *dda, int x, int y, t_img *texture, t_player *player_data)
{
	double	wallX;
	int		tex_x;

	wallX = get_wallX(dda, player_data, x, y);
	tex_x = (int)(wallX * (double)texture->width);
	if (!dda->side && dda->ray.x > 0)
		tex_x = texture->width - tex_x - 1;
	if (dda->side && dda->ray.y < 0)
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}

double	get_wallX(t_dda *dda, t_player *player_data, int x, int y)
{
	double	wallX;
	double	perpwallDist;

	(void)x;
	(void)y;
	perpwallDist = dda->hit_dist;
	if (!dda->side)
		wallX = player_data->pos.y + perpwallDist * dda->ray.y;
	else
		wallX = player_data->pos.x + perpwallDist * dda->ray.x;
	wallX -= floor((wallX));
	return (wallX);
}
