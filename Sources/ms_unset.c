/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 11:03:19 by rficht            #+#    #+#             */
/*   Updated: 2023/06/18 11:08:52 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_env(char *str, char *env)
{
	while (*str && *env)
	{
		if (*str != *env)
			return (FALSE);
		str++;
		env++;
	}
	if (*env == '=' || !(*env))
		return (TRUE);
	else
		return (FALSE);
}

int	ms_env_pos(char *str, char **envp)
{
	int		n;

	n = 0;
	while (envp[n])
	{
		if (is_env(str, envp[n]))
			return (n);
		n++;
	}
	return (-1);
}

void	unset_arg(char *arg, t_ms *ms)
{
	int		i;
	int		j;
	int		pos;
	char	**new_envp;

	pos = ms_env_pos(arg, ms->envp);
	if (pos == -1)
		return ;
	new_envp = ft_calloc((ms_sizeof_tab(ms->envp)), sizeof(char *));
	if (!new_envp)
		ms_crash(ms);
	i = 0;
	j = 0;
	while (ms->envp[i])
	{
		if (i == pos)
			i++;
		new_envp[j++] = ms->envp[i++];
	}
	ft_freestr(&ms->envp[pos]);
	free(ms->envp);
	ms->envp = new_envp;
}

int	ms_unset(t_cmd *cmd)
{
	int	n;

	if (!cmd->args[0])
	{
		printf("ms_unset received NULL args\n");
		return (1);
	}
	n = 1;
	while (cmd->args[n])
	{
		unset_arg(cmd->args[n], cmd->ms);
		n++;
	}
	return (0);
}
