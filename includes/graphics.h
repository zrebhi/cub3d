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

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img;

typedef struct s_graphics
{
	t_img		img_data;
	void		*mlx;
	void		*mlx_win;
	t_parsing	*parse_data;
}				t_graphics;

int		graphics(t_graphics *graphics_data);
void	my_mlx_pixel_put(t_img *img_data, int x, int y, int color);
void	draw_mini_map(t_img *img, t_map *map_data);

#endif
