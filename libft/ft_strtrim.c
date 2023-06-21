/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:36:54 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/23 15:19:42 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		len;
	char	*trimmed;

	if (!set || !ft_strlen(set))
		return (ft_strdup(s1));
	if (!s1)
		return (0);
	len = ft_strlen(s1);
	i = 0;
	j = 0;
	while (s1[i] && ft_is_in(s1[i], set) != -1)
		i++;
	while (len > j && ft_is_in(s1[len - 1 - j], set) != -1)
		j++;
	len -= (i + j);
	trimmed = ft_substr(s1, i, len);
	return (trimmed);
}
