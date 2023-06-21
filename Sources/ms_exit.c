/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:03:52 by rficht            #+#    #+#             */
/*   Updated: 2023/06/14 09:48:12 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_toolong(long long int nbr, char *str)
{
	if (ft_strlen(str) > 20)
		return (TRUE);
	if (nbr >= 0 && *str == '-')
		return (TRUE);
	if (nbr < 0 && *str != '-')
		return (TRUE);
	return (FALSE);
}

static int	isdigit_str(char *str)
{
	while (str && *str)
	{
		if (!ft_isdigit(*str) && *str != '+' && *str != '-')
			return (FALSE);
		str++;
	}
	return (TRUE);
}

static void	exit_test1(t_cmd *cmd)
{
	if (!isdigit_str(cmd->args[1]))
	{
		ft_putstr_fd("msh: exit: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd(" numeric argument required\n", 2);
		ms_free(cmd->ms);
		exit (255);
	}
}

static void	exit_test2(t_cmd *cmd, long return_val)
{
	if (is_toolong(return_val, cmd->args[1]))
	{
		ft_putstr_fd("msh: exit: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd(" numeric argument required\n", 2);
		ms_free(cmd->ms);
		exit (255);
	}
}

int	ms_exit(t_cmd *cmd)
{
	long	return_val;

	printf("\033[1Fmsh > \033[0mexit\n");
	if (!cmd)
		exit(stat_err(-1));
	if (!cmd->args[0])
		return (printf("exit received 0 args\n"), 1);
	printf("exit\n");
	if (!cmd->args[1])
	{
		ms_free(cmd->ms);
		exit(stat_err(-1));
	}
	exit_test1(cmd);
	return_val = ft_atoi(cmd->args[1]);
	exit_test2(cmd, return_val);
	if (cmd->args[2])
		return (ft_putstr_fd("msh: exit : too many arguments\n", 2), 1);
	ms_free(cmd->ms);
	exit(return_val);
	return (0);
}
