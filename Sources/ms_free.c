/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 21:40:22 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/06/19 17:37:47 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_sizeof_tab(char **my_tab)
{
	int	n;

	if (!my_tab)
		return (-1);
	n = 0;
	while (my_tab[n])
		n++;
	return (n);
}

void	ms_pipes_close_free_null(t_ms *ms)
{
	int	i;

	i = -1;
	while (++i < ms->nbcmd - 1)
	{
		close(ms->pipe[i][0]);
		close(ms->pipe[i][1]);
		free(ms->pipe[i]);
		ms->pipe[i] = 0;
	}
	if (ms->pipe)
		free(ms->pipe);
	ms->pipe = 0;
}

/**
 * free every cmds and their content.
 * @param ms the address of minishell
 */
void	ms_free_cmd(t_ms *ms)
{
	int	i;

	i = -1;
	while (++i < ms->nbcmd)
	{
		if (ms->cmd[i].fdin != 0)
			close(ms->cmd[i].fdin);
		if (ms->cmd[i].fdout != 1)
			close(ms->cmd[i].fdout);
		if (ms->cmd[i].filein)
			ft_freenull((void **) &ms->cmd[i].filein);
		if (ms->cmd[i].fileout)
			ft_freenull((void **)&ms->cmd[i].fileout);
		if (ms->cmd[i].args)
			ft_freetab(ms->cmd[i].args);
		if (ms->cmd[i].cmd_name)
			ft_freestr(&(ms->cmd[i].cmd_name));
		if (ms->cmd[i].line)
			ft_freestr(&(ms->cmd[i].line));
		if (ms->cmd[i].path)
			ft_freestr(&(ms->cmd[i].path));
	}
	if (ms->nbcmd)
		ft_freenull((void **) &ms->cmd);
}

/**
 * free all the memory that may have be allocated during the call of a
 * comand line
 * @param ms the address of minishell
 */
void	ms_loop_free(t_ms *ms)
{
	int	i;
	int	err;

	i = -1;
	if (ms->pipe)
		ms_pipes_close_free_null(ms);
	while (++i < ms->nbcmd && ms->pid)
	{
		waitpid(ms->pid[i], &err, 0);
		if (err == 2)
		{
			write(1, "\n", 1);
			stat_err(1);
		}
		else
			stat_err(WEXITSTATUS(err));
	}
	ms_free_cmd(ms);
	if (ms->pid)
		ft_freenull((void **) &ms->pid);
	ms->nbcmd = 0;
	ft_freestr(&ms->line);
	ft_freestr(&ms->rl_str);
}

void	ms_free(t_ms *ms)
{
	int	n;

	n = 0;
	if (ms->envp)
	{
		while (ms->envp[n])
			ft_freestr(&ms->envp[n++]);
	}
	if (!stat_sig(-1))
		ms_loop_free(ms);
	close(ms->histofd);
}
