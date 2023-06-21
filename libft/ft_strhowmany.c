/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strhowmany.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:52:27 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/04/29 15:25:27 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

// move index to the next occurence of c in str. Returns 0 if c was not in str
int	ft_strjumpto(char *str, int *j, char c)
{
	int	bool;
	int	i;

	bool = 0;
	i = *j;
	if (!str[i + 1])
		return (0);
	else
	{
		i++;
		while (str[i] != c)
			i++;
	}
	*j = i;
	return (str[i] == c);
}

// returns the number of occurences of char c in char *str
int	ft_strhowmany(char *str, char c)
{
	int	cpt;
	int	i;

	i = -1;
	cpt = 0;
	while (str[++i])
		if (str[i] == c)
			cpt++;
	return (cpt);
}

int	main(void)
{
	char	*str;
	int		i;

	i = -1;
	str = "les papillons volent gaiement dans les airs|";
	while (str[++i])
	{
		if (str[i] != '|')
			write(1, &str[i], 1);
		if (str[i] == '|')
			ft_strjumpto(str, &i, '|');
	}
	return (0);
}
