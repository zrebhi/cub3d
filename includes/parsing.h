/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:49:58 by zrebhi            #+#    #+#             */
/*   Updated: 2023/05/12 15:48:33 by marobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

int		parsing(int argc, char **argv, t_parsing *parse_data);
void	close_fds(t_colors *colors_data, int mode);

/* Map Parsing */

int		parse_map(t_map *map_data);
void	get_map(t_map *data);
void	fill_map(t_map *data);
int		is_player(char c);
int		space_digits_only(char *str);
int		check_forbidden_char(t_map *data);
int		check_player_count(t_map *data);
int		check_closed_map(t_map *data);
void	replace_map_spaces(t_map *data);

/* Textures and colors */

int		get_colors(t_colors *colors_data, char *file);

#endif
