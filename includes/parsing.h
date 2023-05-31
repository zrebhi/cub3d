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

typedef struct s_parsing	t_parsing;

typedef struct s_map
{
	char		**map;
	int			map_height;
	int			map_width;
	int			fd;
	t_parsing	*parse_data;
}				t_map;

typedef struct s_colors
{
	int			north_texture;
	char		*north_texture_filename;
	int			south_texture;
	char		*south_texture_filename;
	int			west_texture;
	char		*west_texture_filename;
	int			east_texture;
	char		*east_texture_filename;
	int			floor_color;
	int			ceiling_color;
	t_parsing	*parse_data;
}				t_colors;

typedef struct s_parsing
{
	char		*file;
	t_m_free	*m_free;
	t_map		map_data;
	t_colors	colors_data;
}				t_parsing;

int		parsing(int argc, char **argv, t_parsing *parse_data);
void	close_fds(t_colors *colors_data, int mode);

/* Map Parsing */

int		parse_map(t_map *map_data);
int		get_map(t_map *map_data);
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
