/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture_pixel.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:11:48 by zrebhi            #+#    #+#             */
/*   Updated: 2023/06/05 16:52:14 by marobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_tex_x(t_dda *dda, t_img *texture, t_player *player_data);
double	get_wallx(t_dda *dda, t_player *player_data);

int	get_pixel_value(t_img *img, int tex_x, int tex_y)
{
	char	*ptr;
	int		value;

	ptr = img->addr + (tex_y * img->line_length) + (tex_x << 2);
	value = (*(int *)ptr);
	return (value);
}

t_vectori	pixel_coordinates_in_texture(double wall_height, t_img *texture, \
			int y, t_graphics *graphics_data)
{
	t_vectori	coordinates;

	coordinates.y = y * 256 - W_HEIGHT * 128 + wall_height * 128;
	coordinates.y = ((coordinates.y * texture->height) / wall_height) / 256;
	coordinates.x = get_tex_x(&graphics_data->dda, \
	texture, &graphics_data->player_data);
	return (coordinates);
}

int	get_tex_x(t_dda *dda, t_img *texture, t_player *player_data)
{
	double	wall_x;
	int		tex_x;

	wall_x = get_wallx(dda, player_data);
	tex_x = (int)(wall_x * (double)texture->width);
	if (!dda->side && dda->ray.x > 0)
		tex_x = texture->width - tex_x - 1;
	if (dda->side && dda->ray.y < 0)
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}

double	get_wallx(t_dda *dda, t_player *player_data)
{
	double	wall_x;
	double	perpwall_dist;

	perpwall_dist = dda->hit_dist;
	if (!dda->side)
		wall_x = player_data->pos.y + perpwall_dist * dda->ray.y;
	else
		wall_x = player_data->pos.x + perpwall_dist * dda->ray.x;
	wall_x -= (int)((wall_x));
	return (wall_x);
}
