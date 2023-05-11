/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:47:07 by zrebhi            #+#    #+#             */
/*   Updated: 2023/05/11 11:20:23 by marobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_map	data;
	int		i;
	t_game	*game;

	if (argc != 2)
		return (ft_putstr_fd("Invalid number of arguments.\n", 2), 1);
	if (parse_map(argv, &data))
		return (1);
	i = -1;
	printf("\nheight: %d\nmax width: %d\n", data.height, data.width);
	while (data.map[++i])
		printf("%s\n", data.map[i]);
	game = init_game(&data);
	mlx_loop(game->win->mlx_ptr);
}
