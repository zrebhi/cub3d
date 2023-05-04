/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:49:58 by zrebhi            #+#    #+#             */
/*   Updated: 2023/05/03 13:49:58 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

typedef struct s_parsing
{
	char	**map;
	char	*file;
	int		map_height;
	int 	map_width;
}			t_map;

int		parse_map(char **argv, t_map *parse_data);
void	get_map(t_map *data);
void	fill_map(t_map *data);
int		check_forbidden_char(t_map *data);
int		check_player_count(t_map *data);
int		check_closed_map(t_map *data);
void	replace_map_spaces(t_map *data);

#endif
