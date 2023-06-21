/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_where_is.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:31:47 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/03 16:03:59 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

// retourne la position de la premiere occurence de c dans str
int	ft_where_is(char c, char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (-1);
}
