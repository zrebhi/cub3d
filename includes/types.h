/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:13:31 by marobert          #+#    #+#             */
/*   Updated: 2023/05/11 17:14:37 by marobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

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
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	t_img	m_map;
}	t_window;

typedef struct s_vectord
{
	double	x;
	double	y;
}	t_vectord;

typedef struct s_vectori
{
	int	x;
	int	y;
}	t_vectori;

typedef struct s_player
{
	t_vectord	pos;
	t_vectord	dir;
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
	char		*file;
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

typedef struct s_dda
{
	t_vectord	side_dist;
	t_vectori	step;
	t_vectori	box_map;
	t_vectord	delta_dist;
	t_vectord	ray;
	int			side;
}	t_dda;

#endif //TYPES_H
