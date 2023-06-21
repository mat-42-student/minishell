/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdelchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:50:10 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/26 23:11:37 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

// supprime le charactere str[i] dans str
int	ft_strdelchar(char **str_ptr, int i)
{
	char	*str;
	char	*dup;

	str = *str_ptr;
	if (!str || !str[0])
		return (1);
	if ((size_t) i >= ft_sstrlen(str) || i < 0)
		return (0);
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
	dup = ft_strdup(str);
	free(*str_ptr);
	*str_ptr = dup;
	return (0);
}

// supprime tout ce qui suit le charactere str[i] dans str (str[i] = 0) ?!
int	ft_strdelfrom(char *str, int i)
{
	if (!str || !str[0])
		return (1);
	if ((size_t) i >= ft_sstrlen(str) || i < 0)
		return (0);
	str[i] = 0;
	return (0);
}

// supprime nb_del caracteres dans str a partir de str[i]
int	ft_strdelnfrom(char **str, int i, int nb_del)
{
	if (!(*str) || !(*str)[0])
		return (1);
	if ((size_t) i >= ft_sstrlen(*str) || i < 0 || nb_del < 0)
		return (0);
	while (nb_del)
	{
		ft_strdelchar(str, i);
		nb_del--;
	}
	return (0);
}

/*
int	main(void)
{
	char	*str;

	str = ft_strdup("salut");
	ft_printf("original str : %s\n", str);
	ft_strdelnfrom(str, 0, 7);
	ft_printf("truncted str : %s\n", str);
	free(str);
}
*/