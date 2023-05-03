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

#include "cub3d.h"

char	*get_to_the_map(t_parsing *data, int *fd)
{
	char	*str;

	*fd = open(data->file, O_RDONLY);
	while (1)
	{
		str = get_next_line(*fd);
		if (!str)
			return (0);
		if (!ft_strncmp(str, "C", 1))
			break ;
	}
	while (1)
	{
		str = get_next_line(*fd);
		if (!str)
			return (0);
		if (ft_strcmp(str, "\n"))
			break ;
	}
	return (str);
}

void	get_map_height(t_parsing *data, int *fd)
{
	char	*str;

	get_to_the_map(data, fd);
	data->map_height = 1;
	while (1)
	{
		str = get_next_line(*fd);
		if (!str || !ft_strcmp("\n", str))
			break ;
		data->map_height++;
	}
	close(*fd);
}

void	get_map_width(t_parsing *data)
{
	int y;

	data->map_width = 0;
	y = -1;
	while (data->map[++y])
		if ((int)ft_strlen(data->map[y]) > data->map_width)
			data->map_width = ft_strlen(data->map[y]);
}

void	parse_map(t_parsing *data)
{
	int		i;
	int		fd;

	get_map_height(data, &fd);
	data->map = ft_calloc(sizeof(char *), data->map_height + 1);
	if (!data->map)
		exit (1);
	data->map[0] = get_to_the_map(data, &fd);
	i = 0;
	while (++i < data->map_height)
	{
		data->map[i] = get_next_line(fd);
		if (!data->map[i])
			exit(1);
	}
	data->map[i] = 0;
	close (fd);
}

char	*string_filler(t_parsing *data, char *string)
{
	char	*filled_string;
	int		i;

	filled_string = ft_calloc(sizeof(char), data->map_width + 1);
	if (!filled_string)
		exit (1);
	i = 0;
	while(string[i] && string[i] != '\n')
	{
		filled_string[i] = string[i];
		i++;
	}
	while (i < data->map_width - 1)
	{
		filled_string[i] = '1';
		i++;
	}
	return (filled_string);
}

void	fill_map(t_parsing *data)
{
	int y;

	get_map_width(data);
	y = -1;
	while (data->map[++y])
		data->map[y] = string_filler(data, data->map[y]);
}
