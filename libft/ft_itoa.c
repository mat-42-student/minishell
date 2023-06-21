/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 17:38:43 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/04/29 15:25:27 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

int	size(int n)
{
	int	i;

	i = 0;
	if (!n)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	fill(char *ret, long nb, int size, char signe)
{
	int	i;

	i = 0;
	if (!nb)
		ret[0] = '0';
	while (nb)
	{
		ret[size - 1 + signe - i] = nb % 10 + '0';
		nb /= 10;
		i++;
	}
	if (signe)
		ret[0] = '-';
	ret[size + signe] = 0;
}

char	*ft_itoa(int n)
{
	long	nb;
	char	signe;
	char	*ret;

	nb = n;
	signe = 0;
	if (nb < 0)
	{
		signe = 1;
		nb = -nb;
	}
	ret = (char *) malloc(1 + signe + size(nb));
	if (!ret)
		return (NULL);
	fill(ret, nb, size(nb), signe);
	return (ret);
}
