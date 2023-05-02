#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/inc/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_cub
{
	char	**map;
	char	*file;
	int		map_height;
}			t_cub;

#endif