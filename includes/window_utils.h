/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 18:56:35 by mg                #+#    #+#             */
/*   Updated: 2023/05/04 14:06:37 by marobert         ###   ########.fr       */
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

int	create_window(t_map *cub);

#endif //WINDOW_UTILS_H