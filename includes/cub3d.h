/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:52:33 by zrebhi            #+#    #+#             */
/*   Updated: 2023/05/05 18:52:33 by zrebhi           ###   ########.fr       */
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
# include <math.h>

# define FOV 1.0472
# define STEP_Y 10

//t_map	*parse_map(int argc, char **argv);
t_game	*init_game(t_map *map);
int		game_loop(t_game *game);

#endif