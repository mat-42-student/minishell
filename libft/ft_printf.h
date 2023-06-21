/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:46:28 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/04/29 15:25:27 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "../Includes/libft.h"

int		ft_printf(const char *str, ...);
int		replace(char type, va_list *args);
int		ft_idtoa(int n);
int		ft_uitoa(unsigned int n);
int		ft_ctoa(char c);
int		ft_stoa(char *str);
int		ft_xtoa(unsigned long n, char c);
int		ft_ptoa(unsigned long n);
int		idsize(unsigned int n);

#endif
