/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 19:57:04 by zrebhi            #+#    #+#             */
/*   Updated: 2023/05/05 19:57:04 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_file(char *file);
int	get_colors(t_colors *colors_data, char *file);

int	parsing(int argc, char **argv, t_parsing *parse_data)
{
	if (argc != 2)
		return (ft_putstr_fd("Error\nInvalid number of arguments.\n", 2), 1);
	parse_data->m_free = ft_free_init();
	parse_data->file = argv[1];
	parse_data->map_data.parse_data = parse_data;
	parse_data->colors_data.parse_data = parse_data;
	if (check_file(parse_data->file))
		return (ft_free(parse_data->m_free), 1);
	if (parse_map(&parse_data->map_data))
		return (ft_free(parse_data->m_free), 2);
	if (get_colors(&parse_data->colors_data, parse_data->file))
		return (ft_free(parse_data->m_free), 3);
	return (0);
}

int	check_file(char *file)
{
	int	fd;

	if (ft_strcmp(file + (ft_strlen(file) - 4), ".cub"))
	{
		ft_putstr_fd("Error\nFile is not a .cub\n", 2);
		return (1);
	}
	fd = open(file, O_DIRECTORY);
	if (fd != -1)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(" is a directory.\n", 2);
		close(fd);
		return (1);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nInvalid file.\n", 2);
		return (1);
	}
	close(fd);
	return (0);
}

int	get_colors(t_colors *colors_data, char *file)
{
	colors_data->north_texture = open_texture("NO", file, colors_data);
	if (colors_data->north_texture < 0)
		return (ft_putstr_fd("Error\nMissing or invalid north texture.\n", 2), 1);
	colors_data->south_texture = open_texture("SO", file, colors_data);
	if (colors_data->south_texture < 0)
		return (close_fds(colors_data, 1), \
		ft_putstr_fd("Error\nMissing or invalid south texture.\n", 2), 1);
	colors_data->west_texture = open_texture("WE", \
	colors_data->parse_data->file, colors_data);
	if (colors_data->west_texture < 0)
		return (close_fds(colors_data, 2), \
		ft_putstr_fd("Error\nMissing or invalid west texture.\n", 2), 1);
	colors_data->east_texture = open_texture("EA", file, colors_data);
	if (colors_data->east_texture < 0)
		return (close_fds(colors_data, 3), \
		ft_putstr_fd("Error\nMissing or invalid east texture.\n", 2), 1);
	colors_data->floor_color = find_color("F", file, colors_data);
	if (colors_data->floor_color < 0)
		return (close_fds(colors_data, 4), \
		ft_putstr_fd("Error\nMissing or incorrect floor color.\n", 2), 1);
	colors_data->ceiling_color = find_color("C", file, colors_data);
	if (colors_data->ceiling_color < 0)
		return (close_fds(colors_data, 4), \
		ft_putstr_fd("Error\nMissing or incorrect ceiling color.\n", 2), 1);
	return (0);
}

void	close_fds(t_colors *colors_data, int mode)
{
	if (mode == 1)
		close(colors_data->north_texture);
	if (mode == 2)
	{
		close(colors_data->north_texture);
		close(colors_data->south_texture);
	}
	if (mode == 3)
	{
		close(colors_data->north_texture);
		close(colors_data->south_texture);
		close(colors_data->west_texture);
	}
	if (mode == 4)
	{
		close(colors_data->north_texture);
		close(colors_data->south_texture);
		close(colors_data->west_texture);
		close(colors_data->east_texture);
	}
}

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
