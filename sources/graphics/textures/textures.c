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

char	*texture_filename_library(t_colors *colors_data, int i);

void	get_textures(t_graphics *graphics_data, t_colors *colors_data)
{
	int		i;
	char	*texture_filename;

	i = -1;
	while (++i < 4)
	{
		texture_filename = texture_filename_library(colors_data, i);
		graphics_data->textures[i].img = mlx_xpm_file_to_image \
		(graphics_data->mlx, texture_filename, \
		&graphics_data->textures[i].width, &graphics_data->textures[i].height);
		if (!graphics_data->textures[i].img)
		{
			ft_putstr_fd("Error\nInvalid Texture\n", 2);
			exit (1);
		};
		graphics_data->textures[i].addr = mlx_get_data_addr \
		(graphics_data->textures[i].img, \
		&graphics_data->textures[i].bits_per_pixel, \
		&graphics_data->textures[i].line_length, \
		&graphics_data->textures[i].endian);
	}
}

char	*texture_filename_library(t_colors *colors_data, int i)
{
	if (i == 0)
		return (colors_data->north_texture_filename);
	else if (i == 1)
		return (colors_data->south_texture_filename);
	else if (i == 2)
		return (colors_data->east_texture_filename);
	else if (i == 3)
		return (colors_data->west_texture_filename);
	return (0);
}

t_img	wall_orientation_texture(t_dda *dda, t_graphics *graphics_data)
{
	if (dda->side && dda->ray.y > 0)
		return (graphics_data->textures[0]);
	else if (dda->side && dda->ray.y < 0)
		return (graphics_data->textures[1]);
	else if (!dda->side && dda->ray.x < 0)
		return (graphics_data->textures[2]);
	else if (!dda->side && dda->ray.x > 0)
		return (graphics_data->textures[3]);
	return (graphics_data->textures[0]);
}
