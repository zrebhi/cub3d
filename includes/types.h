/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:13:31 by marobert          #+#    #+#             */
/*   Updated: 2023/05/03 19:32:07 by marobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

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
	double	len_x;
	double	len_y;
}	t_vector;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
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
