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

void	get_map_height(t_map *map_data);
char	*get_to_the_map(t_map *map_data);
int		map_is_last(t_map *map_data);

int	parse_map(t_map *map_data)
{
	if (get_map(map_data))
		return (ft_putstr_fd("Error\nInvalid map.\n", 2), 1);
	fill_map(map_data);
	if (check_forbidden_char(map_data))
		return (ft_putstr_fd("Error\nInvalid map (forbidden char).\n", 2), 1);
	if (check_player_count(map_data))
		return (ft_putstr_fd("Error\nInvalid map (player count).\n", 2), 1);
	if (check_closed_map(map_data))
		return (ft_putstr_fd("Error\nInvalid map (not closed).\n", 2), 1);
	if (!map_is_last(map_data))
		return (ft_putstr_fd \
		("Error\nMap must not be split and appear last in the file.\n", 2), 1);
	replace_map_spaces(map_data);
	return (0);
}

int	get_map(t_map *map_data)
{
	int	i;

	get_map_height(map_data);
	map_data->map = ft_calloc(sizeof(char *), \
	map_data->map_height + 1, map_data->parse_data->m_free);
	if (!map_data->map)
		exit (1);
	map_data->map[0] = get_to_the_map(map_data);
	if (!map_data->map[0])
		return (1);
	i = 0;
	while (++i < map_data->map_height)
	{
		map_data->map[i] = get_next_line(map_data->fd, \
		map_data->parse_data->m_free);
		if (!map_data->map[i])
			exit(1);
	}
	map_data->map[i] = 0;
	close (map_data->fd);
	return (0);
}

void	get_map_height(t_map *map_data)
{
	char	*str;

	get_to_the_map(map_data);
	map_data->map_height = 1;
	while (1)
	{
		str = get_next_line(map_data->fd, map_data->parse_data->m_free);
		if (!str || !ft_strcmp("\n", str))
			break ;
		map_data->map_height++;
	}
	close(map_data->fd);
}

char	*get_to_the_map(t_map *map_data)
{
	char	*str;

	map_data->fd = open(map_data->parse_data->file, O_RDONLY);
	while (1)
	{
		str = get_next_line(map_data->fd, map_data->parse_data->m_free);
		if (!str)
		{
			close(map_data->fd);
			return (0);
		}
		if (space_digits_only(str) && ft_strcmp("\n", str))
			break ;
	}
	return (str);
}

int	map_is_last(t_map *map_data)
{
	char	*str;
	int		i;

	str = get_to_the_map(map_data);
	if (!str)
		return (close(map_data->fd), 0);
	i = 0;
	while (++i < map_data->map_height)
	{
		str = get_next_line((map_data->fd), map_data->parse_data->m_free);
		if (!str)
			return (close(map_data->fd), 0);
	}
	while (1)
	{
		str = get_next_line((map_data->fd), map_data->parse_data->m_free);
		if (!str)
			return (close(map_data->fd), 1);
		if (ft_strcmp(str, "\n"))
			return (close(map_data->fd), 0);
	}
}
