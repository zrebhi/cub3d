/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:11:03 by marobert          #+#    #+#             */
/*   Updated: 2023/05/03 19:36:51 by marobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

int	main(int argc, char **argv)
{
	t_map	data;
	int		i;
	t_game	*game;

	i = -1;
	if (argc != 2)
		return (ft_putstr_fd("Invalid number of arguments.\n", 2), 1);
	ft_data_init(&data, argv);
	printf("\nheight: %d\nmax width: %d\n", data.height, data.width);
	while(data.map[++i])
		printf("%s", data.map[i]);
	game = init_game(&data);
	game_loop(game);
}