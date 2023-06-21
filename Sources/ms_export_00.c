/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export_00.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:02:48 by rficht            #+#    #+#             */
/*   Updated: 2023/06/13 16:06:54 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exp_split2(t_export *exp, char *arg, int pos)
{
	exp->name = ft_substr(arg, 0, pos - exp->add);
	exp->value = ft_substr(arg, pos + 1, ft_sstrlen(arg) - pos);
	if (!exp->name || !exp->value)
		return (1);
	return (0);
}

int	exp_split(t_export *exp, char *arg)
{
	int	pos;

	pos = ms_where_is('=', arg);
	exp->add = 0;
	if (pos == -1)
	{
		exp->name = ft_strdup(arg);
		exp->value = 0;
		return (0);
	}
	else if (pos == (int) ft_sstrlen(arg) - 1)
	{
		if (arg[pos - 1] == '+')
		{
			exp->name = ft_substr(arg, 0, pos - 1);
			exp->add = 1;
		}
		else
			exp->name = ft_substr(arg, 0, pos);
		exp->value = "";
		return (0);
	}
	else if (arg[pos - 1] == '+')
		exp->add = 1;
	return (exp_split2(exp, arg, pos));
}

int	ms_exp_init(t_export *exp, char **args, int max)
{
	int	n;

	n = -1;
	while (args[++n])
	{
		if (!ms_valid_name(args[n]))
		{
			ft_putstr_fd("msh: export: not a valid identifier\n", 2);
			return (1);
		}
	}
	n = -1;
	while (args[++n])
	{
		if (exp_split(&exp[n], args[n]))
			return (ms_exp_free(exp, max), 1);
	}
	return (0);
}

t_export	*ms_exp_nullinit(int max)
{
	int			n;
	t_export	*exp;

	exp = malloc((max) * sizeof(t_export));
	if (!exp)
		return (0);
	n = -1;
	while (++n < max)
	{
		exp[n].add = 0;
		exp[n].name = 0;
		exp[n].value = 0;
	}
	return (exp);
}

int	ms_export(t_cmd *cmd)
{
	t_export	*exp;
	int			n;

	if (!cmd || !cmd->args[0])
		return (ft_putstr_fd("msh: export: empty args\n", 2), 1);
	if (!cmd->args[1])
		return (ms_no_arg_export(cmd->ms, cmd->fdout), 0);
	n = 0;
	while (cmd->args[n])
		n++;
	exp = ms_exp_nullinit(n - 1);
	if (!exp)
		return (1);
	if (ms_exp_init(exp, cmd->args + 1, n - 1))
		return (ms_exp_free(exp, n - 1), 1);
	if (ms_exp_all(exp, cmd->ms, n - 1))
		return (ms_exp_free(exp, n - 1), 1);
	ms_exp_free(exp, n - 1);
	return (0);
}
