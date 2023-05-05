/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:13:31 by marobert          #+#    #+#             */
/*   Updated: 2023/05/05 16:22:23 by marobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

//# include "window_utils.h"
/*typedef struct s_cub
{
	char	**map;
	int		height;
	int		width;
}	t_map;*/

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_window
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
}	t_window;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
//	t_vector	vectors[W_WIDTH];
}	t_player;

enum e_dir
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
};

typedef struct s_map
{
	t_img		textures[4];
	int			floor;
	int			ceil;
	char		**map;
	int			height;
	int			width;
	enum e_dir	player_dir;
}	t_map;

typedef struct s_game
{
	t_map		*map;
	t_window	*win;
	t_player	*player;
}	t_game;


#endif //TYPES_H
