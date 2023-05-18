/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zak <zak@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:15:01 by zrebhi            #+#    #+#             */
/*   Updated: 2023/05/18 19:19:03 by zak              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_textures(t_graphics *graphics_data, t_colors *colors_data)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		graphics_data->textures[i].img = mlx_xpm_file_to_image \
		(graphics_data->mlx, colors_data->north_texture_filename, \
		&graphics_data->textures[i].width, &graphics_data->textures[i].height);
		graphics_data->textures[i].addr = mlx_get_data_addr \
		(graphics_data->textures[i].img, \
		&graphics_data->textures[i].bits_per_pixel, \
		&graphics_data->textures[i].line_length, \
		&graphics_data->textures[i].endian);
//		mlx_put_image_to_window(graphics_data->mlx, \
//		graphics_data->mlx_win, graphics_data->textures[i].img, 0, 0);
	}
}

int		side_color(t_dda *dda)
{
	if (dda->side && dda->ray.y > 0)
		return (0xFFFFFF);
	if (dda->side && dda->ray.y < 0)
		return (0x000000);
	if (!dda->side && dda->ray.x < 0)
		return (0xFFFF00);
	if (!dda->side && dda->ray.x > 0)
		return (0x00FFFF);
}

int		get_pixel_value(t_img *img, int x, int y)
{
	char	*ptr;
	int		value;

	ptr = img->addr + (y * img->line_length) + (x << 2);
	value = (*(int *)ptr);
	return (value);
}


double	perpwall_dist(t_dda *dda, t_player *player_data)
{
	double	angle = atan2(dda->ray.y, dda->ray.x);
	double	player_angle = atan2(player_data->dir.y, player_data->dir.x);

	return (dda->hit_dist * cos(angle - player_angle));
}

int	get_tex_x(t_dda *dda, t_player *player_data, int x, int y, t_img *texture)
 {
	double	wallX;
	double	perpwall;
	int		tex_x;
	
	perpwall = perpwall_dist(dda, player_data);
	if (!dda->side)
		wallX = y + perpwall * dda->ray.y;
	else
		wallX = y + perpwall * dda->ray.x;
	wallX -= floor((wallX));
	tex_x = (int)(wallX * (double)texture->width);
	if (!dda->side && dda->ray.x > 0)
		tex_x = texture->width - tex_x - 1;
	if (dda->side && dda->ray.y < 0)
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
 }
 
t_vectori pixel_coordinates_in_texture(double wall_height, t_img *texture, int x, int y, t_dda *dda, t_player *player_data)
{
    t_vectori coordinates;

    coordinates.y = y * 256 - W_HEIGHT * 128 + wall_height * 128;
    coordinates.y = ((coordinates.y * texture->height) / wall_height) / 256;
	coordinates.x = get_tex_x(dda, player_data, x, y, texture);

    return (coordinates);
}