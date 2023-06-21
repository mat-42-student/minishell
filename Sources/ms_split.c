/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:11:41 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/06/01 08:55:16 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	quotesplit_crash(t_ms *ms, t_list **lst)
{
	ft_lstclear(lst, free);
	ms_crash(ms);
}

static int	cut_add(t_list **lst, char *s, int i, int j)
{
	char	*section;
	t_list	*new_elem;

	section = ft_substr(s, i, j - i);
	if (!section)
		return (1);
	new_elem = ft_lstnew(section);
	if (!new_elem)
	{
		ft_freestr(&section);
		return (1);
	}
	ft_lstadd_back(lst, new_elem);
	return (0);
}

static void	ms_next_word_quote(char *str, char sep, int *i, int *j)
{
	*i = *j;
	while (!ms_quote_status(str, *i) && str[*i] == sep)
		(*i)++;
	if (str[*i])
		*j = *i + 1;
	else
		*j = *i;
}

static t_list	*ms_quote_init(char *str, char sep, int *i, int *j)
{
	*j = 0;
	ms_next_word_quote(str, sep, i, j);
	return (0);
}

/**
 * split a string arround sepparators that are not between quotes. 
 * @param s string that we want to split.
 * @param sep the separator that will delimit the split.
 * @return str array of the sections we obtained.
 */
char	**ms_quotesplit(char *s, char sep, t_ms *ms)
{
	t_list	*l;
	int		i;
	int		j;
	char	**result;

	l = ms_quote_init(s, sep, &i, &j);
	while (s[j])
	{
		if (s[i] != sep && (s[j] == sep && !ms_quote_status(s, j)))
		{
			if (cut_add(&l, s, i, j))
				quotesplit_crash(ms, &l);
			ms_next_word_quote(s, sep, &i, &j);
		}
		else
			j++;
	}
	if (j != i && s[j] != sep)
		if (cut_add(&l, s, i, j))
			quotesplit_crash(ms, &l);
	result = ft_lst_to_strtab(l);
	if (!result)
		quotesplit_crash(ms, &l);
	return (result);
}

/*
int	main(void)
{
	char	**split;

	split = ms_quotesplit("'Ceci est un test||| ' de decoup", '|');
	ft_printstrtab(split, "SPLIT");
	ft_freetab(split);
	//system("leaks a.out");
	return (0);
}
*/