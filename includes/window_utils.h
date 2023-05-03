/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 18:56:35 by mg                #+#    #+#             */
/*   Updated: 2023/05/03 21:03:29 by marobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_UTILS_H
# define WINDOW_UTILS_H

# include "libft.h"
# include "mlx.h"
# include "cub3d.h"
# include "utils.h"

# define TITLE "Cub3D"
# define W_HEIGHT 650
# define W_WIDTH 1700

int	create_window(t_map *cub);

#endif //WINDOW_UTILS_H
