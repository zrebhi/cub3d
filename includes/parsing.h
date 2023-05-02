#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

typedef struct s_parsing
{
	char	**map;
	char	*file;
	int		map_height;
}			t_parsing;

int	check_forbidden_char(t_parsing *data);
int	check_player_count(t_parsing *data);

#endif
