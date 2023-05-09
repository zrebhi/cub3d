/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 18:56:35 by mg                #+#    #+#             */
/*   Updated: 2023/05/09 17:09:55 by marobert         ###   ########.fr       */
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
# define W_HEIGHT 650
# define W_WIDTH 1700

# define COL_PLAYER 0x00FF00BB
# define COL_WALL 0x0
# define COL_EMPTY 0x00FFFFFF

int		create_window(t_map *cub);
void	put_pxl_img(t_img *img, int x, int y, int color);
void	draw_lines(t_game *game, t_window *win, t_player *player, t_map *map);

#endif //WINDOW_UTILS_H
