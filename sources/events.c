/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 15:43:30 by marobert          #+#    #+#             */
/*   Updated: 2023/10/14 15:43:37 by marobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

int	key_pressed(int key, t_graphics *graphics_data)
{
	if (key == KEY_ESC)
		exit_window(graphics_data);
	else
		graphics_data->keys[key] = 1;
	return (1);
}

int	key_released(int key, t_graphics *graphics_data)
{
	graphics_data->keys[key] = 0;
	return (1);
}
