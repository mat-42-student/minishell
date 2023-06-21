/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotesplit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:27:59 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/05/12 20:33:03 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

void	ft_next_word_quote(char *str, char sep, int *i, int *j)
{
	*i = *j;
	while (str[*i] == sep)
		(*i)++;
	if (str[*i] == '\'')
	{
		*j = *i + 1;
		while (str[*j] && str[*j] != '\'')
			(*j)++;
	}
	else if (str[*i])
		*j = *i + 1;
	else
		*j = *i;
}

t_list	*quote_init(char *str, char sep, int *i, int *j)
{
	*j = 0;
	ft_next_word_quote(str, sep, i, j);
	return (0);
}

char	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (c);
	return (0);
}

char	**ft_quotesplit(char *s, char sep)
{
	t_list	*l;
	int		i;
	int		j;
	char	quote;

	l = quote_init(s, sep, &i, &j);
	while (s[j])
	{
		quote = is_quote(s[j]);
		if (s[i] != sep && (s[j] == sep || quote))
		{
			if (s[i] == quote)
				ft_lstadd_back(&l, ft_lstnew(ft_substr(s, i + 1, j++ - i - 1)));
			else
				ft_lstadd_back(&l, ft_lstnew(ft_substr(s, i, j - i)));
			ft_next_word_quote(s, sep, &i, &j);
		}
		else
			j++;
	}
	if (j != i && s[j] != sep)
		ft_lstadd_back(&l, ft_lstnew(ft_substr(s, i, j - i)));
	return (ft_lst_to_strtab(l));
}
/*
int	main(void)
{
	char	**split;

	split = ft_quotesplit("Ceci est un test||| de decoupage rigolo ?", '|');
	ft_printstrtab(split, "-- SPLIT --");
	ft_freetab(split);
	//system("leaks a.out");
	return (0);
}
*/