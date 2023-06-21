/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 11:36:39 by rficht            #+#    #+#             */
/*   Updated: 2023/06/12 11:05:13 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	n_flag_val(char **args)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (*args == 0)
		return (0);
	if (ft_strequal(*args, "-n"))
		return (1);
	while (args[i + 1])
		i++;
	while (args[i][j])
		j++;
	if (j < 2)
		return (0);
	if (args[i][j - 1] == 'c' && args[i][j - 2] == '\\')
		return (1);
	return (0);
}

int	write_args(char **args, int fdout, int n_flag)
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

	if (!cmd->args[0])
	{
		printf("echo received 0 args\n");
		return (1);
	}
	n = 1;
	n_flag = n_flag_val(cmd->args + n);
	if (n_flag == TRUE)
		n++;
	if (write_args(cmd->args + n, cmd->fdout, n_flag))
		return (1);
	return (0);
}
