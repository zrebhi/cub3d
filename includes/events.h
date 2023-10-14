/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 15:44:03 by marobert          #+#    #+#             */
/*   Updated: 2023/10/14 15:44:08 by marobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# include "cub3d.h"

int	key_pressed(int key, t_graphics *graphics_data);
int	key_released(int key, t_graphics *graphics_data);

#endif //EVENTS_H
