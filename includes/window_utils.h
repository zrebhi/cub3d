/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:32:54 by marobert          #+#    #+#             */
/*   Updated: 2023/05/02 18:38:14 by marobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_UTILS_H
# define WINDOW_UTILS_H

# include "libft.h"
# include "mlx.h"
# include "cub3d.h"

# define TITLE "Cub3D"
# define W_HEIGHT 650
# define W_WIDTH 1700

int	create_window(t_cub *cub);

#endif //WINDOW_UTILS_H
