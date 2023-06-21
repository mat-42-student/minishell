/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstrtab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:32:06 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/05 10:48:05 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

void	ft_printstrtab(char **str_tab, char *titre)
{
	ft_printf(GREEN"--- %s ---\n"RESET, titre);
	while (str_tab && *str_tab)
	{
		ft_printf("%s\n", *str_tab);
		str_tab++;
	}
	ft_printf(GREEN"--- END ---\n"RESET);
}
