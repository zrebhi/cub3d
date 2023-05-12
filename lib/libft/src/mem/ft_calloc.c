/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:49:17 by cpalusze          #+#    #+#             */
/*   Updated: 2022/11/12 08:28:24 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t count, size_t size, t_m_free *m_free)
{
	void	*ptr;

	if (size && count > SIZE_MAX / size)
		return (0);
	ptr = ft_free_malloc(m_free, count * size);
	if (ptr == NULL)
	{
		ft_free(m_free);
		exit(1);
	}
	ft_memset(ptr, 0, count * size);
	return (ptr);
}
