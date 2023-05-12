/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:47:07 by zrebhi            #+#    #+#             */
/*   Updated: 2023/05/11 16:12:19 by marobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_map	data;
	t_game	*game;

	if (argc != 2)
		return (ft_putstr_fd("Invalid number of arguments.\n", 2), 1);
	if (parse_map(argv, &data))
		return (1);
	printf("\nheight:\t%d\nwidth:\t%d\n", data.height, data.width);
	for (int i = 0; i < data.height; ++i)
	{
		for (int j = 0; j < data.width; ++j)
		{
			if (data.map[i][j] == '1')
				printf("█");
			else if (ft_isalpha(data.map[i][j]))
				printf("x");
			else
				printf(" ");
		}
		printf("\n");
	}
	game = init_game(&data);
	mlx_loop(game->win->mlx_ptr);
	return (ft_free(parse_data.m_free), \
	close_fds(&parse_data.colors_data, 4), 0);
}
