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
}			t_parsing;

void	parse_map(t_parsing *data);
void	fill_map(t_parsing *data);
int		check_forbidden_char(t_parsing *data);
int		check_player_count(t_parsing *data);
int		check_closed_map(t_parsing *data);

#endif
