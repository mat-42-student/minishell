/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:46:07 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/06/07 17:03:12 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"
#include <stdio.h>

long long	ft_atoi(const char *str)
{
	int		signe;
	size_t	nb;

	signe = 1;
	nb = 0;
	if (ft_strequal((char *)str, "-9223372036854775808"))
		return (-9223372036854775807 -1);
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signe = -signe;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10 + *str - 48;
		str++;
	}
	return (nb * signe);
}
