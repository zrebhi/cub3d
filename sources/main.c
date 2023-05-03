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

void	ft_data_init(t_parsing *data, char **argv)
{
	data->file = argv[1];
	parse_map(data);
	fill_map(data);
}

int	main(int argc, char **argv)
{
	t_parsing	data;

	if (argc != 2)
		return (ft_putstr_fd("Invalid number of arguments.\n", 2), 1);
	ft_data_init(&data, argv);
	if (check_forbidden_char(&data))
		return (ft_putstr_fd("Invalid map (forbidden char).\n", 2), 2);
	if (check_player_count(&data))
		return (ft_putstr_fd("Invalid map (player count).\n", 2), 3);
	if (check_closed_map(&data))
		return (ft_putstr_fd("Invalid map (not closed).\n", 2), 4);
}
