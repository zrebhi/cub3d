/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:01:05 by marobert          #+#    #+#             */
/*   Updated: 2023/05/11 10:32:51 by marobert         ###   ########.fr       */
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
