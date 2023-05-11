/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:01:05 by marobert          #+#    #+#             */
/*   Updated: 2023/05/11 14:36:38 by marobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	in_range(int value, int start, int end)
{
	return (value > start && value < end);
}

t_vectord	rotate(t_vectord vector, double angle)
{
	t_vectord	new;

	new.x = vector.x * cos(angle) - vector.y * sin(angle);
	new.y = vector.x * sin(angle) + vector.y * cos(angle);
	return (new);
}

int	get_color_side(t_dda *dda)
{
	if (dda->side == 1 && dda->ray.y > 0) 	// N
		return (0x4367e8); 					// BLEU
	else if (dda->side == 1) 				// S
		return (0x56ed34); 					// VERT
	else if (dda->ray.x > 0) 				// W
		return (0xd1d12c); 					// JAUNE
	else 									// E
		return (0xdb3f37); 					// ROUGE
}
