/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:32:54 by marobert          #+#    #+#             */
/*   Updated: 2023/05/02 16:30:07 by marobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_UTILS_H
# define WINDOW_UTILS_H

# include "libft.h"
# include "mlx.h"
# include "cub3d.h"

# define TITLE "Cub3D"
# define W_HEIGHT 1000
# define W_WIDTH 1000

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_window {
	void		*mlx_ptr;
	void		*win_ptr;
	t_data		img;
	t_cub		*cub_ptr;
}	t_window;

int	create_window(t_cub *cub);

#endif //WINDOW_UTILS_H
