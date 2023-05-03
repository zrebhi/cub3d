/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_destroy_display.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mg <mg@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 18:56:35 by mg                #+#    #+#             */
/*   Updated: 2020/10/04 01:55:35 by mg               ###   ########.fr       */
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
