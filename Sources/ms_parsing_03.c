/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:43:11 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/06/08 17:43:32 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * return TRUE or FALSE depending on whether inapropriate char sequences 
 * are found or not.
 * @param str line of commande after spaces have been trimed.
 */
int	ms_wrongchars(char	*str)
{
	int	i;
	int	last;

	last = ft_sstrlen(str) - 1;
	if (ms_checkpipes(str) || str[0] == '|' || str[last] == '|')
		return (ms_error_msg(SYN_EUNEXT"|", TRUE));
	if (ms_badchev(str) || str[last] == '<' || str[last] == '>')
		return (ms_error_msg(SYN_EUNEXT"< or >", TRUE));
	i = -1;
	while (str[++i])
		if (!ms_quote_status(str, i) && ft_is_in(str[i], FORBID_CHAR) != -1)
			return (ms_error_msg(SYN_EUNEXT FORBID_CHAR, TRUE));
	return (FALSE);
}
