/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_hashignore.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 11:37:45 by rficht            #+#    #+#             */
/*   Updated: 2023/06/15 09:54:34 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_comment(char *str, int n)
{
	if (n == 0)
		return (TRUE);
	n--;
	if (str[n] == ' ')
		return (TRUE);
	return (FALSE);
}

char	*str_cut(char *str, int n)
{
	char	*result;

	if ((size_t) n > ft_strlen(str) || !str)
	{
		printf("str_cur received invalid arg \n");
		return (NULL);
	}
	result = ft_calloc((n + 1), sizeof(char));
	while (n)
	{
		result[n] = str[n];
		n--;
	}
	free(str);
	str = NULL;
	return (result);
}

char	*ms_trim_hashtag(char *str)
{
	int	n;

	n = 0;
	while (str[n])
	{
		if (str[n] == '#' && ms_quote_status(str, n) == 0)
		{
			if (is_comment(str, n))
				return (str_cut(str, n));
		}
		n++;
	}
	return (str);
}
