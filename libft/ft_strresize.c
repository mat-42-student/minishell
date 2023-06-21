/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strresize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:09:16 by rficht            #+#    #+#             */
/*   Updated: 2023/05/26 23:12:59 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

int	ft_strresize(char **str_ptr, int val)
{
	int		old_len;
	int		new_len;
	char	*new_str;
	int		n;

	if (!(*str_ptr))
		return (1);
	n = -1;
	old_len = ft_strlen(*str_ptr);
	new_len = old_len + val;
	if (new_len <= 0)
		return (1);
	new_str = ft_calloc(new_len + 1, sizeof(char *));
	if (!new_str)
		return (1);
	if (val < 0)
		while (++n < new_len)
			new_str[n] = (*str_ptr)[n];
	else
		while (++n < old_len)
			new_str[n] = (*str_ptr)[n];
	free(*str_ptr);
	*str_ptr = new_str;
	return (0);
}
