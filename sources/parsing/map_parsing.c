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

int	space_digits_only(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]) && str[i] != ' ' && str[i] != '\n')
			return (0);
	}
	return (1);
}

char	*get_to_the_map(t_map *map_data, int *fd)
{
	char	*str;

	*fd = open(map_data->parse_data->file, O_RDONLY);
	while (1)
	{
		str = get_next_line(*fd, map_data->parse_data->m_free);
		if (!str)
			return (0);
		if (space_digits_only(str) && ft_strcmp("\n", str))
			break ;
	}
	return (str);
}

void	get_map_height(t_map *map_data, int *fd)
{
	char	*str;

	get_to_the_map(map_data, fd);
	map_data->map_height = 1;
	while (1)
	{
		str = get_next_line(*fd, map_data->parse_data->m_free);
		if (!str || !ft_strcmp("\n", str))
			break ;
		map_data->map_height++;
	}
	close(*fd);
}

void	get_map(t_map *map_data)
{
	int	i;
	int	fd;

	get_map_height(map_data, &fd);
	map_data->map = ft_calloc(sizeof(char *), \
	map_data->map_height + 1, map_data->parse_data->m_free);
	if (!map_data->map)
		exit (1);
	map_data->map[0] = get_to_the_map(map_data, &fd);
	i = 0;
	while (++i < map_data->map_height)
	{
		map_data->map[i] = get_next_line(fd, map_data->parse_data->m_free);
		if (!map_data->map[i])
			exit(1);
	}
	map_data->map[i] = 0;
	close (fd);
}

int	parse_map(t_map *map_data)
{
	get_map(map_data);
	fill_map(map_data);
	if (check_forbidden_char(map_data))
		return (ft_putstr_fd("Invalid map (forbidden char).\n", 2), 1);
	if (check_player_count(map_data))
		return (ft_putstr_fd("Invalid map (player count).\n", 2), 1);
	if (check_closed_map(map_data))
		return (ft_putstr_fd("Invalid map (not closed).\n", 2), 1);
	replace_map_spaces(map_data);
	return (0);
}
