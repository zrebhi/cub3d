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

#  define Q 12
#  define W 13
#  define E 14
#  define A 0
#  define S 1
#  define D 2
#  define ARROW_L 123
#  define ARROW_R 124
#  define ESC 53

# endif //DARWIN

# if LINUX == 1

#  define W 'w'
#  define S 's'
#  define A 'a'
#  define D 'd'
#  define Q 'q'
#  define E 'e'
#  define ARROW_L 65361
#  define ARROW_R 65363
#  define ESC 65307

# endif //LINUX


#endif