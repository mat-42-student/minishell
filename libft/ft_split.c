/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:14:34 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/04/29 15:25:27 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/libft.h"

char	*put_word(int deb, int fin, char *str)
{
	char	*word;
	int		size;
	int		j;

	j = 0;
	size = fin - deb;
	word = (char *) malloc(size + 1);
	if (!word)
		return (NULL);
	while (deb + j < fin)
	{
		word[j] = str[deb + j];
		j++;
	}
	word[j] = 0;
	return (word);
}

int	how_many_words(char *str, char sep)
{
	int	i;
	int	words;
	int	lettre;

	words = 0;
	i = 0;
	lettre = 0;
	while (str[i])
	{
		if (sep == str[i])
			lettre = 0;
		else
		{
			if (!lettre)
				words++;
			lettre = 1;
		}
		i++;
	}
	return (words);
}

char	**check_wa(char **wa, int *len)
{
	int	i;

	i = 0;
	while (wa[i] && i <= *len)
	{
		if (*wa[i])
			i++;
	}
	if (i == *len)
		return (wa);
	else
	{
		i = 0;
		while (i <= *len)
			free(wa[i++]);
		free(wa);
		return (NULL);
	}
}

char	**fill_word_arr(char **wa, char *str, char sep)
{
	int	i;
	int	ideb;
	int	iword;

	i = 1;
	iword = 0;
	if (str[0] != sep)
		ideb = 0;
	while (str[0] && str[i])
	{
		if (str[i] != sep && str[i - 1] == sep)
			ideb = i;
		if (str[i] == sep && str[i - 1] != sep)
			wa[iword++] = put_word(ideb, i, str);
		if (str[i] != sep && !str[i + 1])
			wa[iword++] = put_word(ideb, i + 1, str);
		i++;
	}
	wa[iword] = 0;
	wa = check_wa(wa, &iword);
	return (wa);
}

char	**ft_split(char const *str, char sep)
{
	int		words_number;
	char	**tab;

	if (!str)
		return (0);
	words_number = how_many_words((char *) str, sep);
	tab = (char **) malloc((1 + words_number) * sizeof (tab));
	if (!tab)
		return (NULL);
	if (ft_sstrlen(str) == 1)
	{
		if (str[0] != sep)
		{
			tab[0] = (char *) str;
			tab[1] = 0;
		}
		else
			tab[0] = 0;
	}
	else
		tab = fill_word_arr(tab, (char *) str, sep);
	return (tab);
}
