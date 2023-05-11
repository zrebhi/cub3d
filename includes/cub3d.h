/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:37:20 by marobert          #+#    #+#             */
/*   Updated: 2023/05/04 13:37:20 by marobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "types.h"
# include "window_utils.h"
# include "parsing.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# define FOV 1.0472
# define STEP_Y 10

//t_map	*parse_map(int argc, char **argv);
t_game	*init_game(t_map *map);
int		game_loop(t_game *game);

#endif