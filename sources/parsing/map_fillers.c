/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_fillers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:28:29 by zrebhi            #+#    #+#             */
/*   Updated: 2023/05/04 13:45:40 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_fillers.c                                       :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:24:15 by zrebhi            #+#    #+#             */
/*   Updated: 2023/05/04 12:28:18 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	get_width(t_map *map_data)
{
	int	y;

	map_data->width = 0;
	y = -1;
	while (map_data->map[++y])
		if ((int)ft_strlen(map_data->map[y]) - 1 > map_data->width)
			map_data->width = (int)ft_strlen(map_data->map[y]) - 1;
}

char	*string_filler(t_map *map_data, char const *string)
{
	char	*filled_string;
	int		i;

	filled_string = ft_calloc(sizeof(char), map_data->width + 1, \
	map_data->parse_data->m_free);
	if (!filled_string)
		exit (1);
	i = 0;
	while (string[i] && string[i] != '\n')
	{
		filled_string[i] = string[i];
		i++;
	}
	while (i < map_data->width)
	{
		filled_string[i] = ' ';
		i++;
	}
	return (filled_string);
}

void	fill_map(t_map *map_data)
{
	int	y;

	get_width(map_data);
	y = -1;
	while (map_data->map[++y])
		map_data->map[y] = string_filler(map_data, map_data->map[y]);
}

char	*replace_str_spaces(char *str, t_map *map_data)
{
	char	*new_string;
	int		i;

	new_string = ft_calloc(sizeof(char), ft_strlen(str) + 1, \
	map_data->parse_data->m_free);
	if (!new_string)
		return (0);
	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ')
			new_string[i] = '1';
		else
			new_string[i] = str[i];
	}
	return (new_string);
}

void	replace_map_spaces(t_map *map_data)
{
	int	y;

	y = -1;
	while (map_data->map[++y])
		map_data->map[y] = replace_str_spaces(map_data->map[y], map_data);
}
