/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:19:34 by mdjemaa           #+#    #+#             */
/*   Updated: 2022/11/25 13:05:57 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	div_bybase(unsigned long n, char *base, int	*count)
{
	char	c;

	if (n / 16 > 0)
		if (div_bybase(n / 16, base, count) == -1)
			return (-1);
	c = base[n % 16];
	if (write(1, &c, 1) == -1)
		return (-1);
	return ((*count)++);
}

int	ft_xtoa(unsigned long n, char c)
{
	int		count;
	char	*base;

	if (c == 'x')
		base = "0123456789abcdef";
	if (c == 'X')
		base = "0123456789ABCDEF";
	count = 0;
	if (div_bybase(n, base, &count) == -1)
		return (-1);
	return (count);
}

int	ft_ptoa(unsigned long n)
{
	int		count;
	char	*base;

	base = "0123456789abcdef";
	if (write(1, "0x", 2) == -1)
		return (-1);
	count = 2;
	if (div_bybase(n, base, &count) == -1)
		return (-1);
	return (count);
}
