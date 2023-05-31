/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrebhi <zrebhi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:31:46 by zrebhi            #+#    #+#             */
/*   Updated: 2023/05/31 14:31:46 by zrebhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	space_digits_only(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]) && str[i] != ' ' && str[i] != '\n')
			return (0);
	}
	return (1);
}

char	*ft_remove_backslashn(char *str, t_colors *colors_data)
{
	char	*new_str;
	int		i;

	new_str = ft_calloc(sizeof(char), ft_strlen(str), \
	colors_data->parse_data->m_free);
	if (!new_str)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = 0;
	return (new_str);
}
