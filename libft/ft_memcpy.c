/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 18:30:21 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/04/29 15:25:27 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void			*dst0;
	size_t			i;
	unsigned char	*tmpdst;
	unsigned char	*tmpsrc;

	i = 0;
	dst0 = dst;
	if (!src && !dst && n)
		return (dst0);
	tmpdst = (unsigned char *) dst;
	tmpsrc = (unsigned char *) src;
	while (i < n)
	{
		tmpdst[i] = tmpsrc[i];
		i++;
	}
	dst = tmpdst;
	return (dst0);
}
