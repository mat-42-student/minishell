/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrunc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:17:09 by rficht            #+#    #+#             */
/*   Updated: 2023/05/28 14:15:49 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"
#include <stdio.h>

static int	is_valid(char *str, int start, int len)
{
	int	n;

	n = 0;
	while (str[n] && n < start + len)
		n++;
	if (n == start + len)
		return (1);
	else
		return (0);
}

int	ft_strtrunc(char **str, int start, int len)
{
	int		n;
	char	*result;

	if (!str || !(*str))
		return (1);
	n = start;
	if (!is_valid(*str, start, len))
		return (1);
	while ((*str)[n + len])
	{
		(*str)[n] = (*str)[n + len];
		n++;
	}
	(*str)[n] = 0;
	result = ft_strdup(*str);
	free(*str);
	*str = result;
	return (0);
}
