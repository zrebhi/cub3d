/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:47:07 by zrebhi            #+#    #+#             */
/*   Updated: 2023/05/03 13:48:00 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_parsing	parse_data;
	t_graphics	graphics_data;

	ft_bzero(graphics_data.keys, 70000);
	if (parsing(argc, argv, &parse_data))
		return (1);
	graphics_data.parse_data = &parse_data;
	if (graphics(&graphics_data))
		return (2);
	return (ft_free(parse_data.m_free), \
	close_fds(&parse_data.colors_data, 4), 0);
}

int	exit_window(t_graphics *graphics_data)
{
	int	i;

	i = -1;
	while (++i < 4)
		mlx_destroy_image(graphics_data->mlx, graphics_data->textures[i].img);
	mlx_destroy_image(graphics_data->mlx, graphics_data->img_data.img);
	mlx_destroy_image(graphics_data->mlx, graphics_data->map_img_data.img);
	mlx_destroy_window(graphics_data->mlx, graphics_data->mlx_win);
	if (LINUX)
		mlx_destroy_display(graphics_data->mlx);
	free(graphics_data->mlx);
	close_fds(&graphics_data->parse_data->colors_data, 4);
	ft_free(graphics_data->parse_data->m_free);
	exit (0);
}
