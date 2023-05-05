/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:59:29 by marobert          #+#    #+#             */
/*   Updated: 2023/05/04 14:25:32 by marobert         ###   ########.fr       */
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
# define SPEED 3

void		rotate_left(t_player *player);
void		rotate_right(t_player *player);
void		forward(t_player *player);
void		backward(t_player *player);
t_player	*init_player(t_map *map);

#endif //PLAYER_UTILS_H
