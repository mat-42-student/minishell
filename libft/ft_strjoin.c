/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:27:25 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/04/29 15:25:27 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	size_t	i;
	char	*s3;

	size = ft_sstrlen(s1) + ft_sstrlen(s2);
	s3 = malloc(size + 1);
	if (!s3)
		return (0);
	i = 0;
	if (s1)
		while (*s1)
			s3[i++] = *(s1++);
	if (s2)
		while (*s2)
			s3[i++] = *(s2++);
	s3[i] = 0;
	return (s3);
}
