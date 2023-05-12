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

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_parsing	parse_data;
	t_graphics	graphics_data;

	if (parsing(argc, argv, &parse_data))
		return (1);
	graphics_data.parse_data = &parse_data;
	if (graphics(&graphics_data))
		return (2);
	return (ft_free(parse_data.m_free), \
	close_fds(&parse_data.colors_data, 4), 0);
}
