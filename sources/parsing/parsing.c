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
int	unknown_texture(char *file, t_colors *colors_data);

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
		return (ft_free(parse_data->m_free), 4);
	if (unknown_texture(parse_data->file, &parse_data->colors_data))
		return (ft_putstr_fd("Error\nUnknown texure in file.\n", 2), \
		ft_free(parse_data->m_free), 3);
	return (0);
}

int	unknown_texture(char *file, t_colors *colors_data)
{
	char	*str;
	int		fd;

	fd = open(file, O_RDONLY);
	while (1)
	{
		str = get_next_line(fd, colors_data->parse_data->m_free);
		if (!str)
			return (close(fd), 0);
		if (space_digits_only(str) && ft_strcmp("\n", str))
			return (close(fd), 0);
		if (ft_strcmp(str, "\n") && ft_strncmp(str, "NO", 2) && \
		ft_strncmp(str, "SO", 2) && ft_strncmp(str, "EA", 2) && \
		ft_strncmp(str, "WE", 2) && ft_strncmp(str, "F", 1) && \
		ft_strncmp(str, "C", 1))
			return (close(fd), 1);
	}
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
