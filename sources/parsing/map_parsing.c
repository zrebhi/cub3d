/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:32:06 by zrebhi            #+#    #+#             */
/*   Updated: 2023/05/03 13:59:59 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int		get_map_height(char **file);
int		get_map_first_line(char **file);
int		map_is_last(t_map *map_data, char **file);

int	parse_map(t_map *map_data, char **file)
{
	if (get_map(map_data, file))
		return (ft_putstr_fd("Error\nInvalid map.\n", 2), 1);
	fill_map(map_data);
	if (check_forbidden_char(map_data))
		return (ft_putstr_fd("Error\nInvalid map (forbidden char).\n", 2), 1);
	if (check_player_count(map_data))
		return (ft_putstr_fd("Error\nInvalid map (player count).\n", 2), 1);
	if (check_closed_map(map_data))
		return (ft_putstr_fd("Error\nInvalid map (not closed).\n", 2), 1);
	if (!map_is_last(map_data, file))
		return (ft_putstr_fd \
		("Error\nMap must not be split and appear last in the file.\n", 2), 1);
	replace_map_spaces(map_data);
	return (0);
}

int	get_map(t_map *map_data, char **file)
{
	int	i;
	int	line;

	map_data->map_height = get_map_height(file);
	if (map_data->map_height == -1)
		return (1);
	map_data->map = ft_calloc(sizeof(char *), \
	map_data->map_height + 1, map_data->parse_data->m_free);
	line = get_map_first_line(file);
	i = 0;
	while (i < map_data->map_height)
		map_data->map[i++] = file[line++];
	map_data->map[i] = 0;
	return (0);
}

int	get_map_height(char **file)
{
	int		line;
	int		map_height;

	line = get_map_first_line(file);
	if (line == -1)
		return (-1);
	map_height = 0;
	while (file[line])
	{
		if (!ft_strcmp("\n", file[line]))
			return (map_height);
		map_height++;
		line++;
	}
	return (map_height);
}

int	get_map_first_line(char **file)
{
	int		line;

	line = -1;
	while (file[++line])
	{
		if (space_digits_only(file[line]) && ft_strcmp("\n", file[line]))
			return (line);
	}
	return (-1);
}

int	map_is_last(t_map *map_data, char **file)
{
	int		line;
	int		map_last_line;

	map_last_line = get_map_first_line(file) + map_data->map_height;
	line = map_last_line;
	if (!file[line])
		return (1);
	while (file[line])
	{
		if (ft_strcmp(file[line], "\n"))
			return (0);
		line++;
	}
	return (1);
}
