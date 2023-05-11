/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 18:56:35 by mg                #+#    #+#             */
/*   Updated: 2023/05/11 18:14:52 by marobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_UTILS_H
# define WINDOW_UTILS_H

# include "libft.h"
# include "mlx.h"
# include "cub3d.h"
# include "utils.h"
# include "player_utils.h"

# define TITLE "Cub3D"
# define W_HEIGHT 1080
# define W_WIDTH 1920

void	put_pxl_img(t_img *img, int x, int y, int color);
void	draw_lines(t_game *game, t_window *win, t_player *player, t_map *map);
void	draw_map(t_img *img, t_player *player, t_map *map);
void	draw_vector(t_img *img, t_vectord position, t_vectori direction, \
					t_map *map);

#endif //WINDOW_UTILS_H
