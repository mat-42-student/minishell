/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:11:38 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/04/29 15:25:27 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	size_t			diff;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	diff = 0;
	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	while (i < n && diff == 0)
	{
		diff = str1[i] - str2[i];
		if (diff)
			return (diff);
		i++;
	}
	return (diff);
}
