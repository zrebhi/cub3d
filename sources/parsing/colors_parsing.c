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

#include "cub3d.h"

int		open_texture(char *id, char **file, t_colors *colors_data);
char	*find_texture_filename(char *id, char **file, t_colors *colors_data);
int		duplicate_texture(char *id, char **file, int line);
int		find_color(char *id, char **file, t_colors *colors_data);

int	get_colors(t_colors *colors_data, char **file)
{
	colors_data->north_texture = open_texture("NO ", file, colors_data);
	if (colors_data->north_texture < 0)
		return (ft_putstr_fd("Error\nMissing or invalid north texture.\n", 2), 1);
	colors_data->south_texture = open_texture("SO ", file, colors_data);
	if (colors_data->south_texture < 0)
		return (close_fds(colors_data, 1), \
		ft_putstr_fd("Error\nMissing or invalid south texture.\n", 2), 1);
	colors_data->west_texture = open_texture("WE ", \
	colors_data->parse_data->file, colors_data);
	if (colors_data->west_texture < 0)
		return (close_fds(colors_data, 2), \
		ft_putstr_fd("Error\nMissing or invalid west texture.\n", 2), 1);
	colors_data->east_texture = open_texture("EA ", file, colors_data);
	if (colors_data->east_texture < 0)
		return (close_fds(colors_data, 3), \
		ft_putstr_fd("Error\nMissing or invalid east texture.\n", 2), 1);
	colors_data->floor_color = find_color("F ", file, colors_data);
	if (colors_data->floor_color < 0)
		return (close_fds(colors_data, 4), \
		ft_putstr_fd("Error\nMissing or incorrect floor color.\n", 2), 1);
	colors_data->ceiling_color = find_color("C ", file, colors_data);
	if (colors_data->ceiling_color < 0)
		return (close_fds(colors_data, 4), \
		ft_putstr_fd("Error\nMissing or incorrect ceiling color.\n", 2), 1);
	return (0);
}

int	open_texture(char *id, char **file, t_colors *colors_data)
{
	int		fd;
	char	*texture_filename;

	texture_filename = find_texture_filename(id, file, colors_data);
	if (!texture_filename)
		return (-1);
	if (!ft_strcmp("NO ", id))
		colors_data->north_texture_filename = texture_filename;
	if (!ft_strcmp("SO ", id))
		colors_data->south_texture_filename = texture_filename;
	if (!ft_strcmp("EA ", id))
		colors_data->east_texture_filename = texture_filename;
	if (!ft_strcmp("WE ", id))
		colors_data->west_texture_filename = texture_filename;
	fd = open(texture_filename, O_RDONLY);
	return (fd);
}

char	*find_texture_filename(char *id, char **file, t_colors *colors_data)
{
	int		line;
	int		i;

	line = 0;
	while (file[line])
	{
		if (!ft_strncmp(file[line], id, ft_strlen(id)))
			break ;
		line++;
	}
	if (!file[line])
		return (NULL);
	i = (int)ft_strlen(id);
	while (file[line][i] == ' ')
		i++;
	if (duplicate_texture(id, file, line))
		return (NULL);
	return (ft_remove_backslashn(file[line] + i, colors_data));
}

int	duplicate_texture(char *id, char **file, int line)
{
	while (file[++line])
	{
		if (!ft_strncmp(file[line], id, ft_strlen(id)))
			return (1);
	}
	return (0);
}

int	find_color(char *id, char **file, t_colors *colors_data)
{
	char	**split_color_code;
	char	*color_code;
	int		i;
	int		colors[3];

	color_code = find_texture_filename(id, file, colors_data);
	if (!color_code)
		return (-1);
	split_color_code = \
	ft_split(color_code, ',', colors_data->parse_data->m_free);
	i = -1;
	while (split_color_code[++i])
	{
		colors[i] = ft_atoi(split_color_code[i]);
		if (colors[i] < 0 || colors[i] > 255)
			return (-1);
	}
	if (i != 3)
		return (-1);
	return (colors[0] * 65536 + colors[1] * 256 + colors[2]);
}
