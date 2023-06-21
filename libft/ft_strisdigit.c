/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisdigit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:30:00 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/04/29 15:25:27 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

int	ft_strisdigit(const char *str)
{
	int	i;
	int	size;

	if (!str || !*str)
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	size = ft_sstrlen(str);
	if (!size)
		return (0);
	i = -1;
	while (++i < size)
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}
