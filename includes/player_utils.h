/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:59:29 by marobert          #+#    #+#             */
/*   Updated: 2023/05/10 12:18:49 by marobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_UTILS_H
# define PLAYER_UTILS_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include "types.h"
# include "window_utils.h"

# define ROTATE 0.2
# define SPEED 1

void		rotate_left(t_player *player);
void		rotate_right(t_player *player);
void		forward(t_player *player, int dir);
t_player	*init_player(t_map *map);

#endif //PLAYER_UTILS_H
