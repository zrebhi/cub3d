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

int	check_texture(char *id, int fd, t_colors *colors_data);

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
	if (check_texture(id, fd, colors_data))
		return (close(fd), NULL);
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
	if (!ft_strcmp("NO", id))
		colors_data->north_texture_filename = str;
	if (!ft_strcmp("SO", id))
		colors_data->south_texture_filename = str;
	if (!ft_strcmp("EA", id))
		colors_data->east_texture_filename = str;
	if (!ft_strcmp("WE", id))
		colors_data->west_texture_filename = str;
	fd = open(str, O_RDONLY);
	return (fd);
}

int	check_texture(char *id, int fd, t_colors *colors_data)
{
	char	*str;

	while (1)
	{
		str = get_next_line(fd, colors_data->parse_data->m_free);
		if (!str)
			return (0);
		if (!ft_strncmp(str, id, ft_strlen(id)))
			return (1);
	}
}

long	find_color(char *id, char *file, t_colors *colors_data)
{
	char	**strs;
	char	*str;
	int		i;
	int		colors[3];

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
	return (colors[0] * 65536 + colors[1] * 256 + colors[2]);
}
