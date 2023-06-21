/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamat <mamat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:50:04 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/06/20 00:58:22 by mamat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_do_builtin(t_cmd	*cmd)
{
	if (cmd->invalidfd)
		return (stat_err(ms_check_fds(*cmd)));
	if (ft_strequal(cmd->cmd_name, "cd"))
		return (ms_cd(cmd));
	if (ft_strequal(cmd->cmd_name, "echo"))
		return (ms_echo(cmd));
	if (ft_strequal(cmd->cmd_name, "env"))
		return (ms_env(cmd));
	if (ft_strequal(cmd->cmd_name, "exit"))
		return (ms_exit(cmd));
	if (ft_strequal(cmd->cmd_name, "export"))
		return (ms_export(cmd));
	if (ft_strequal(cmd->cmd_name, "pwd"))
		return (ms_pwd(cmd));
	if (ft_strequal(cmd->cmd_name, "unset"))
		return (ms_unset(cmd));
	return (1);
}

void	ms_fixfds(t_cmd	*cmd)
{
	int	i;

	i = cmd->nb;
	if (!cmd->filein && !cmd->limiter)
	{
		if (i == 0)
			cmd->fdin = 0;
		else
			cmd->fdin = cmd->ms->pipe[i - 1][0];
	}
	if (!cmd->fileout)
	{
		if (i == cmd->ms->nbcmd - 1)
			cmd->fdout = 1;
		else
			cmd->fdout = cmd->ms->pipe[i][1];
	}
	ms_exit_check_fds(*cmd);
}

void	ms_child(t_ms *ms, int i)
{
	char	*pathcmd;

	ms_close_pipes_but(ms, i);
	ms_fixfds(&ms->cmd[i]);
	dup2(ms->cmd[i].fdin, 0);
	dup2(ms->cmd[i].fdout, 1);
	if (ms_isbuiltin(ms->cmd[i].cmd_name))
		exit(ms_do_builtin(&ms->cmd[i]));
	else
	{
		pathcmd = ft_strjoin(ms->cmd[i].path, ms->cmd[i].cmd_name);
		if (!pathcmd)
			return ;
		if (ms->cmd[i].path && !ft_strequal(ms->cmd[i].cmd_name, ""))
			execve(pathcmd, ms->cmd[i].args, ms->envp);
		//ft_freenull((void **)&pathcmd);
		ms_bad_child_ending(pathcmd);
	}
}

int	ms_exec(t_ms *ms)
{
	int	i;

	if (ms->nbcmd == 1 && ms_isbuiltin(ms->cmd[0].cmd_name))
		return (stat_err(ms_do_builtin(&ms->cmd[0])));
	ms->pid = ft_calloc(ms->nbcmd, sizeof(int));
	if (!ms->pid)
		return (1);
	i = -1;
	stat_sig(disabled);
	while (++i < ms->nbcmd)
	{
		ms->pid[i] = fork();
		if (!ms->pid[i])
		{
			stat_sig(child);
			ms_child(ms, i);
		}
	}
	return (0);
}
