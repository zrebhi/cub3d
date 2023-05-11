/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marobert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:00:52 by marobert          #+#    #+#             */
/*   Updated: 2023/05/11 10:33:09 by marobert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <math.h>
# include "types.h"

int			in_range(int value, int start, int end);
t_vectord	rotate(t_vectord vector, double angle);
int			get_color_side(t_dda *dda);

#endif //UTILS_H
