/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:45:28 by rficht            #+#    #+#             */
/*   Updated: 2023/05/26 23:12:45 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

//insert str2 dans str1 a l'index pos (free str1) si str2 NULL ne fait rieng
int	ft_strinsert(char **str1, char *str2, int pos)
{
	char	*result;
	int		i;
	int		j;

	if (!str1 || !(*str1))
		return (1);
	if (!(str2))
		return (0);
	i = -1;
	j = -1;
	if ((size_t) pos > ft_strlen(*str1))
		return (1);
	result = ft_calloc((ft_strlen(*str1) + ft_strlen(str2) + 1), sizeof(char));
	while (++i < pos)
		result[i] = (*str1)[i];
	while (str2[++j])
		result[i + j] = str2[j];
	while ((*str1)[i])
	{
		result[i + j] = (*str1)[i];
		i++;
	}
	free(*str1);
	*str1 = result;
	return (0);
}
