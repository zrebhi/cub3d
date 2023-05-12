/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:47:07 by zrebhi            #+#    #+#             */
/*   Updated: 2023/05/12 16:08:18 by marobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_map		map;
	t_game		*game;
	t_parsing	parse_data;

	if (argc != 2)
		return (ft_putstr_fd("Invalid number of arguments.\n", 2), 1);
	if (parsing(argc, argv, &parse_data))
		return (1);
	map = parse_data.map_data;
	map.ceil = parse_data.colors_data.ceiling_color;
	map.floor = parse_data.colors_data.floor_color;
	printf("\nheight:\t%d\nwidth:\t%d\n", map.height, map.width);
	for (int i = 0; i < map.height; ++i)
	{
		for (int j = 0; j < map.width; ++j)
		{
			__attribute__((unused)) char a = map.map[i][j];
			if (map.map[i][j] == '1')
				printf("█");
			else if (ft_isalpha(map.map[i][j]))
				printf("x");
			else
				printf(" ");
		}
		printf("\n");
	}
	game = init_game(&map);
	mlx_loop(game->win->mlx_ptr);
	return (ft_free(parse_data.m_free), \
			close_fds(&parse_data.colors_data, 4), 0);
}
