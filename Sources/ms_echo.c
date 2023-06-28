/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 11:36:39 by rficht            #+#    #+#             */
/*   Updated: 2023/06/28 16:18:29 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_flags(char *arg, int *n_flag)
{
	int	n;

	if (!arg)
		return (FALSE);
	if (arg[0] != '-')
		return (FALSE);
	n = 0;
	while (arg[++n])
	{
		if (arg[n] == 'n')
			*n_flag = TRUE;
		else
			return (FALSE);
	}
	return (TRUE);
}

static int	write_args(char **args, int fdout, int n_flag)
{
	while (args[0])
	{
		if (ft_putstr_fd(args[0], fdout) == -1)
			return (1);
		args++;
		if (args[0])
		{
			if (write(fdout, " ", 1) == -1)
				return (1);
		}
	}
	if (!n_flag)
	{
		if (write(fdout, "\n", 1) == -1)
			return (1);
	}
	return (0);
}

int	ms_echo(t_cmd *cmd)
{
	int	n_flag;
	int	n;

	n_flag = 0;
	if (!cmd->args[0])
	{
		printf("echo received 0 args\n");
		return (1);
	}
	n = 1;
	while (check_flags(cmd->args[n], &n_flag))
		n++;
	if (write_args(cmd->args + n, cmd->fdout, n_flag))
		return (1);
	return (0);
}
