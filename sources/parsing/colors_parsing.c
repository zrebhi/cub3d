/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:52:51 by zrebhi            #+#    #+#             */
/*   Updated: 2023/05/04 13:52:51 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*ft_remove_backslashn(char *str, t_colors *colors_data)
{
	char	*new_str;
	int		i;

	new_str = ft_calloc(sizeof(char), ft_strlen(str), \
	colors_data->parse_data->m_free);
	if (!new_str)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = 0;
	return (new_str);
}

char	*find_texture(char *id, char *file, t_colors *colors_data)
{
	char	*str;
	int		fd;
	int		i;

	fd = open(file, O_RDONLY);
	while (1)
	{
		str = get_next_line(fd, colors_data->parse_data->m_free);
		if (!str)
			return (0);
		if (!ft_strncmp(str, id, ft_strlen(id)))
			break ;
	}
	i = (int)ft_strlen(id);
	while (str[i] == ' ')
		i++;
	close(fd);
	return (ft_remove_backslashn(str + i, colors_data));
}

int	open_texture(char *id, char *file, t_colors *colors_data)
{
	int		fd;
	char	*str;

	str = find_texture(id, file, colors_data);
	if (!str)
		return (-1);
	fd = open(str, O_RDONLY);
	return (fd);
}

long	find_color(char *id, char *file, t_colors *colors_data)
{
	char	**strs;
	char	*str;
	int		i;
	int		colors[3];
	long	color;

	str = find_texture(id, file, colors_data);
	if (!str)
		return (-1);
	strs = ft_split(str, ',', colors_data->parse_data->m_free);
	i = -1;
	while (strs[++i])
	{
		colors[i] = ft_atoi(strs[i]);
		if (colors[i] < 0 || colors[i] > 255)
			return (-1);
	}
	if (i != 3)
		return (-1);
	color = colors[0] * 255 + colors[1] * (long)pow(255, 2) + \
			colors[2] * (long)pow(255, 3);
	return (color);
}

int	get_colors(t_colors *colors_data, char *file)
{
	colors_data->north_texture = open_texture("NO", file, colors_data);
	if (colors_data->north_texture < 0)
		return (ft_putstr_fd("Missing or invalid north texture.\n", 2), 1);
	colors_data->south_texture = open_texture("SO", file, colors_data);
	if (colors_data->south_texture < 0)
		return (close_fds(colors_data, 1), \
		ft_putstr_fd("Missing or invalid south texture.\n", 2), 1);
	colors_data->west_texture = open_texture("WE", \
	colors_data->parse_data->file, colors_data);
	if (colors_data->west_texture < 0)
		return (close_fds(colors_data, 2), \
		ft_putstr_fd("Missing or invalid west texture.\n", 2), 1);
	colors_data->east_texture = open_texture("EA", file, colors_data);
	if (colors_data->east_texture < 0)
		return (close_fds(colors_data, 3), \
		ft_putstr_fd("Missing or invalid east texture.\n", 2), 1);
	colors_data->floor_color = find_color("F", file, colors_data);
	if (colors_data->floor_color < 0)
		return (close_fds(colors_data, 4), \
		ft_putstr_fd("Missing or incorrect floor color.\n", 2), 1);
	colors_data->ceiling_color = find_color("C", file, colors_data);
	if (colors_data->ceiling_color < 0)
		return (close_fds(colors_data, 4), \
		ft_putstr_fd("Missing or incorrect ceiling color.\n", 2), 1);
	return (0);
}