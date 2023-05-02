/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:13:31 by marobert          #+#    #+#             */
/*   Updated: 2023/05/02 17:17:08 by marobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct s_cub
{
	char	**map;
	int		map_height;
	int		map_mwidth;
}	t_cub;

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
}	t_window;

#endif //TYPES_H
