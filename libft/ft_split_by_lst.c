/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_by_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:27:59 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/04/29 15:25:27 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

void	ft_next_word(char *str, char sep, int *i, int *j)
{
	*i = *j;
	while (str[*i] == sep)
		(*i)++;
	if (str[*i])
		*j = *i + 1;
	else
		*j = *i;
}

char	**ft_split_by_lst(char *str, char sep)
{
	t_list	*lst;
	int		i;
	int		j;

	lst = 0;
	j = 0;
	ft_next_word(str, sep, &i, &j);
	while (str[j])
	{
		if (str[i] != sep && str[j] == sep)
		{
			ft_lstadd_back(&lst, ft_lstnew(ft_substr(str, i, j - i)));
			ft_next_word(str, sep, &i, &j);
		}
		else
			j++;
	}
	if (j != i && str[j] != sep)
		ft_lstadd_back(&lst, ft_lstnew(ft_substr(str, i, j - i)));
	return (ft_lst_to_strtab(lst));
}
/*
int	main(void)
{
	char	**split;

	split = ft_split_by_lst("le petit chat est mignon mais il a faim", ' ');
	ft_printstrtab(split, "-- SPLIT --");
	ft_freetab(split);
	system("leaks a.out");
	return (0);
}
*/
