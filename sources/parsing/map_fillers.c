/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_fillers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:28:29 by zrebhi            #+#    #+#             */
/*   Updated: 2023/05/04 12:28:29 by zrebhi           ###   ########.fr       */
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

void	get_map_width(t_map *parse_data)
{
	int	y;

	parse_data->map_width = 0;
	y = -1;
	while (parse_data->map[++y])
		if ((int)ft_strlen(parse_data->map[y]) - 1 > parse_data->map_width)
			parse_data->map_width = ft_strlen(parse_data->map[y]) - 1;
}

char	*string_filler(t_map *parse_data, char *string)
{
	char	*filled_string;
	int		i;

	filled_string = ft_calloc(sizeof(char), parse_data->map_width + 1);
	if (!filled_string)
		exit (1);
	i = 0;
	while (string[i] && string[i] != '\n')
	{
		filled_string[i] = string[i];
		i++;
	}
	while (i < parse_data->map_width)
	{
		filled_string[i] = filled_string[i - 1];
		i++;
	}
	return (filled_string);
}

void	fill_map(t_map *parse_data)
{
	int	y;

	get_map_width(parse_data);
	y = -1;
	while (parse_data->map[++y])
		parse_data->map[y] = string_filler(parse_data, parse_data->map[y]);
}

char	*replace_str_spaces(char *str)
{
	char	*new_string;
	int		i;

	new_string = ft_calloc(sizeof(char), ft_strlen(str) + 1);
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

void	replace_map_spaces(t_map *parse_data)
{
	int	y;

	y = -1;
	while (parse_data->map[++y])
		parse_data->map[y] = replace_str_spaces(parse_data->map[y]);
}
