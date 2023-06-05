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
# include "parsing.h"
# include "graphics.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>


/* OS Depending */

# ifndef DARWIN
#  define DARWIN 0
# endif //DARWIN

# ifndef LINUX
#  define LINUX 0
# endif //LINUX

# if DARWIN == 1

#  define KEY_Q 12
#  define KEY_W 13
#  define KEY_E 14
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_ARROW_L 123
#  define KEY_ARROW_R 124
#  define KEY_ESC 53

# endif //DARWIN

# if LINUX == 1

#  define KEY_W 'w'
#  define KEY_S 's'
#  define KEY_A 'a'
#  define KEY_D 'd'
#  define KEY_Q 'q'
#  define KEY_E 'e'
#  define KEY_ARROW_L 65361
#  define KEY_ARROW_R 65363
#  define KEY_ESC 65307

# endif //LINUX


#endif