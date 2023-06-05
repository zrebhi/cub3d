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

char	**parse_file(t_parsing *parse_data, char *filename);
int		get_file_size(char *filename, t_parsing *parse_data);
int		check_file(char *filename);
int		unknown_texture(t_parsing *parse_data);

int	parsing(int argc, char **argv, t_parsing *parse_data)
{
	if (argc != 2)
		return (ft_putstr_fd("Error\nInvalid number of arguments.\n", 2), 1);
	parse_data->m_free = ft_free_init();
	if (check_file(argv[1]))
		return (ft_free(parse_data->m_free), 1);
	parse_data->file = parse_file(parse_data, argv[1]);
	if (!parse_data->file)
		return (ft_free(parse_data->m_free), 2);
	parse_data->map_data.parse_data = parse_data;
	parse_data->colors_data.parse_data = parse_data;
	if (unknown_texture(parse_data))
		return (ft_putstr_fd("Error\nUnknown texure in file.\n", 2), \
		ft_free(parse_data->m_free), 3);
	if (parse_map(&parse_data->map_data, parse_data->file))
		return (ft_free(parse_data->m_free), 4);
	if (get_colors(&parse_data->colors_data, parse_data->file))
		return (ft_free(parse_data->m_free), 5);
	return (0);
}

char	**parse_file(t_parsing *parse_data, char *filename)
{
	char	**file;
	int		file_size;
	int		fd;
	int		line;

	file_size = get_file_size(filename, parse_data);
	if (file_size == -1)
		return (NULL);
	file = ft_calloc(sizeof(char *), file_size, parse_data->m_free);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	line = 0;
	while (1)
	{
		file[line] = get_next_line(fd, parse_data->m_free);
		if (!file[line])
			break ;
		line++;
	}
	close(fd);
	return (file);
}

int	get_file_size(char *filename, t_parsing *parse_data)
{
	int		fd;
	int		file_size;
	char	*str;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	file_size = 0;
	while (1)
	{
		str = get_next_line(fd, parse_data->m_free);
		file_size++;
		if (!str)
			break ;
	}
	close(fd);
	return (file_size);
}

int	unknown_texture(t_parsing *parse_data)
{
	int	i;

	i = -1;
	while (parse_data->file[++i])
	{
		if (space_digits_only(parse_data->file[i]) \
		&& ft_strcmp("\n", parse_data->file[i]))
			return (0);
		if (ft_strcmp(parse_data->file[i], "\n") && \
		ft_strncmp(parse_data->file[i], "NO ", 3) && \
		ft_strncmp(parse_data->file[i], "SO ", 3) && \
		ft_strncmp(parse_data->file[i], "EA ", 3) && \
		ft_strncmp(parse_data->file[i], "WE ", 3) && \
		ft_strncmp(parse_data->file[i], "F ", 2) && \
		ft_strncmp(parse_data->file[i], "C ", 2))
			return (1);
	}
	return (0);
}

int	check_file(char *filename)
{
	int	fd;

	if (ft_strcmp(filename + (ft_strlen(filename) - 4), ".cub"))
	{
		ft_putstr_fd("Error\nFile is not a .cub\n", 2);
		return (1);
	}
	fd = open(filename, O_DIRECTORY);
	if (fd != -1)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(" is a directory.\n", 2);
		close(fd);
		return (1);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nInvalid file.\n", 2);
		return (1);
	}
	close(fd);
	return (0);
}
