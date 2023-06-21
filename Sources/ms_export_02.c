/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export_02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:24:12 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/06/15 09:53:41 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_exp_addvar(t_export *exp, t_ms *ms)
{
	char	**new_envp;
	int		n;

	n = -1;
	new_envp = ft_calloc(ms_sizeof_tab(ms->envp) + 2, sizeof(char *));
	if (!new_envp)
		return (1);
	while (ms->envp[++n])
		new_envp[n] = ms->envp[n];
	if (exp->value)
		new_envp[n] = ft_strmanyjoin(exp->name, "=", exp->value, 0);
	else
		new_envp[n] = ft_strdup(exp->name);
	if (!new_envp[n])
		return (1);
	free(ms->envp);
	ms->envp = new_envp;
	return (0);
}

int	ms_valid_name(char *new_var)
{
	if (!ft_isalpha(*new_var) && *new_var != '_')
		return (FALSE);
	while (*new_var && *new_var != '=')
	{
		if (*new_var == '+')
		{
			if (*(new_var + 1) == '=')
				return (TRUE);
			return (FALSE);
		}
		if (!ft_isalnum(*new_var) && *new_var != '_')
			return (FALSE);
		new_var++;
	}
	return (TRUE);
}

void	ms_exp_free(t_export *exp, int max)
{
	int	n;

	n = -1;
	while (++n < max)
	{
		if (exp[n].name)
			ft_freestr(&exp[n].name);
		if (exp[n].value && !ft_strequal(exp[n].value, ""))
			ft_freestr(&exp[n].value);
	}
	free(exp);
}

/**
 * export a new var into ms_env. Carefull, it doesn't free new var.
 * @param exp the new variable to export.
 * @param ms a pointer to minishell.
 * @return 0 if succes 1 if fail. 
 */
int	ms_exp_one(t_export *exp, t_ms *ms)
{
	int	env_varl;

	env_varl = ms_getenv_varl(exp->name, ms);
	if (env_varl == -1 && env_exp_addvar(exp, ms))
		return (1);
	if (env_varl >= 0 && !exp->add && exp->value)
	{
		free(ms->envp[env_varl]);
		ms->envp[env_varl] = ft_strmanyjoin(exp->name, "=", exp->value, 0);
		if (!ms->envp[env_varl])
			return (1);
	}
	else if (env_varl >= 0 && exp->add && exp->value)
	{
		if (ms_where_is('=', ms->envp[env_varl]) == -1)
			if (ft_strinsert(&ms->envp[env_varl], "=",
					ft_strlen(ms->envp[env_varl])))
				return (1);
		if (ft_strinsert(&ms->envp[env_varl], exp->value,
				ft_strlen(ms->envp[env_varl])))
			return (1);
	}
	return (0);
}

int	ms_exp_all(t_export *exp, t_ms *ms, int max)
{
	int	n;

	n = -1;
	while (++n < max)
	{
		if (ms_exp_one(&exp[n], ms))
			return (1);
	}
	return (0);
}
