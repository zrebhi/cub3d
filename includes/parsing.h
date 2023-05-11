/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:49:58 by zrebhi            #+#    #+#             */
/*   Updated: 2023/05/11 11:13:03 by marobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

int		parse_map(char **argv, t_map *parse_data);
void	get_map(t_map *data);
void	fill_map(t_map *data);
int		check_forbidden_char(t_map *data);
int		is_player(char c);
int		check_player_count(t_map *data);
int		check_closed_map(t_map *data);
void	replace_map_spaces(t_map *data);

#endif
