/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:21:20 by zrebhi            #+#    #+#             */
/*   Updated: 2023/05/03 11:21:20 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_forbidden_char(char c)
{
	int		i;
	char	*possible_chars;

	possible_chars = "01NSWE \n";
	i = -1;
	while (possible_chars[++i])
	{
		if (c == possible_chars[i])
			return (0);
	}
	return (1);
}

int	check_forbidden_char(t_map *parse_data)
{
	int	x;
	int	y;

	y = -1;
	while (parse_data->map[++y])
	{
		x = -1;
		while (parse_data->map[y][++x])
			if (is_forbidden_char(parse_data->map[y][x]))
				return (1);
	}
	return (0);
}

int	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

int	check_player_count(t_map *parse_data)
{
	int	x;
	int	y;
	int	player_count;

	player_count = 0;
	y = -1;
	while (parse_data->map[++y])
	{
		x = -1;
		while (parse_data->map[y][++x])
		{
			if (is_player(parse_data->map[y][x]))
				player_count++;
			if (player_count > 1)
				return (1);
		}
	}
	if (player_count == 1)
		return (0);
	else
		return (1);
}
