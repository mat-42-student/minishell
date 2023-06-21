/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:53:52 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/04/29 15:25:27 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	size;
	size_t	i;

	if (!s || start >= ft_strlen(s))
	{
		subs = malloc(1);
		if (!subs)
			return (0);
		subs[0] = 0;
		return (subs);
	}
	size = ft_min(ft_strlen(s) - start, len);
	subs = malloc(size + 1);
	if (!subs)
		return (0);
	i = 0;
	while (i < size)
	{
		subs[i] = s[start + i];
		i++;
	}
	subs[i] = 0;
	return (subs);
}
