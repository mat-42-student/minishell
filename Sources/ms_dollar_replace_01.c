/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_dollar_replace_01.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:44:35 by rficht            #+#    #+#             */
/*   Updated: 2023/06/18 14:49:04 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_env_valid_char(char *str, int pos)
{
	if (pos == 0)
	{
		if (!ft_isalpha(str[pos]) && str[pos] != '_')
			return (FALSE);
	}
	else if (!ft_isalnum(str[pos]) && str[pos] != '_')
		return (FALSE);
	return (TRUE);
}

static int	next_empty_dol_pos(char *str, t_ms *ms)
{
	int	n;

	n = 0;
	if (!str)
		return (-1);
	while (str[n])
	{
		if (is_doll_replaced(str, n) && !ms_getenv_val(&str[n + 1], ms))
			return (n);
		n++;
	}
	return (-1);
}

int	ms_trim_empty_dolls(char **str, t_ms *ms)
{
	int	empty_dol_pos;

	empty_dol_pos = next_empty_dol_pos(*str, ms);
	while (empty_dol_pos != (-1))
	{
		if (dol_replace(str, empty_dol_pos, ms))
			return (1);
		empty_dol_pos = next_empty_dol_pos(*str, ms);
	}
	return (0);
}
