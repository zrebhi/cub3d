/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:55:43 by zrebhi            #+#    #+#             */
/*   Updated: 2023/05/12 18:55:43 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "cub3d.h"
# include <mlx.h>

# define FOV 90
# define W_WIDTH 1920
# define W_HEIGHT 1080

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img;

typedef struct s_vectord
{
	double	x;
	double	y;
}			t_vectord;

typedef struct s_vectori
{
	int	x;
	int	y;
}	t_vectori;

typedef struct s_player
{
	t_vectord	pos;
	t_vectord	dir;
}				t_player;

typedef struct s_dda
{
	t_vectord	side_dist;
	t_vectori	step;
	t_vectori	box_map;
	t_vectord	delta_dist;
	t_vectord	ray;
	double		hit_dist;
	int			side;
}	t_dda;

typedef struct s_graphics
{
	t_img		img_data;
	t_img		map_img_data;
	void		*mlx;
	void		*mlx_win;

	t_player	player_data;
	t_dda		dda;
	t_parsing	*parse_data;
}				t_graphics;

int		graphics(t_graphics *graphics_data);
void	my_mlx_pixel_put(t_img *img_data, int x, int y, int color);
void	mini_map(t_img *img, t_map *map_data, \
		t_player *player_data, t_graphics *graphics_data);
void	draw_lines(t_graphics *graphics_data, t_player *player);

/* Player */

void	init_player(char ***map, t_player *player_data);
void	move_forward(t_player *player, int dir, char **map);
void	move_aside(t_player *player, int dir, char **map);
void	rotate_side(t_player *player, int dir);

#endif
