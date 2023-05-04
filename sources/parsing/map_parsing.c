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

char	*get_to_the_map(t_map *parse_data, int *fd)
{
	char	*str;

	*fd = open(parse_data->file, O_RDONLY);
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

void	get_map_height(t_map *parse_data, int *fd)
{
	char	*str;

	get_to_the_map(parse_data, fd);
	parse_data->map_height = 1;
	while (1)
	{
		str = get_next_line(*fd);
		if (!str || !ft_strcmp("\n", str))
			break ;
		parse_data->map_height++;
	}
	close(*fd);
}

void	get_map(t_map *parse_data)
{
	int		i;
	int		fd;

	get_map_height(parse_data, &fd);
	parse_data->map = ft_calloc(sizeof(char *), parse_data->map_height + 1);
	if (!parse_data->map)
		exit (1);
	parse_data->map[0] = get_to_the_map(parse_data, &fd);
	i = 0;
	while (++i < parse_data->map_height)
	{
		parse_data->map[i] = get_next_line(fd);
		if (!parse_data->map[i])
			exit(1);
	}
	parse_data->map[i] = 0;
	close (fd);
}

void	ft_parse_data_init(t_map *parse_data, char **argv)
{
	parse_data->file = argv[1];
	get_map(parse_data);
	fill_map(parse_data);
}

int	parse_map(char **argv, t_map *parse_data)
{
	ft_parse_data_init(parse_data, argv);
	if (check_forbidden_char(parse_data))
		return (ft_putstr_fd("Invalid map (forbidden char).\n", 2), 1);
	if (check_player_count(parse_data))
		return (ft_putstr_fd("Invalid map (player count).\n", 2), 1);
	if (check_closed_map(parse_data))
		return (ft_putstr_fd("Invalid map (not closed).\n", 2), 1);
	replace_map_spaces(parse_data);
	return (0);
}
