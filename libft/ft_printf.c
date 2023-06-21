/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:45:05 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/01/04 17:17:12 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	replace(char type, va_list *args)
{
	if (type == 'i' || type == 'd')
		return (ft_idtoa(va_arg(*args, int)));
	if (type == 'u')
		return (ft_uitoa(va_arg(*args, unsigned int)));
	if (type == '%')
		return (ft_ctoa('%'));
	if (type == 'c')
		return (ft_ctoa(va_arg(*args, int)));
	if (type == 's')
		return (ft_stoa(va_arg(*args, char *)));
	if (type == 'p')
		return (ft_ptoa(va_arg(*args, unsigned long)));
	if (type == 'x' || type == 'X')
		return (ft_xtoa(va_arg(*args, unsigned int), type));
	return (-1);
}

void	printf_init(int *a, int *b)
{
	*a = 0;
	*b = -1;
}

int	ft_printf(const char *base, ...)
{
	va_list	args;
	int		i;
	int		count;
	int		res;

	printf_init(&count, &i);
	va_start(args, base);
	while (base[++i])
	{
		if (base[i] == '%')
		{
			res = replace(base[++i], &args);
			if (res == -1)
				return (-1);
			count += res;
		}
		else
		{
			if (write(1, &base[i], 1) == -1)
				return (-1);
			count++;
		}
	}
	va_end(args);
	return (count);
}
