/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:18:24 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/06/14 11:19:54 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_get_next_fd(t_cmd *cmd)
{
	int	in;
	int	out;

	while ((ms_where_is('<', cmd->line) != -1 || \
		ms_where_is('>', cmd->line) != -1) && !cmd->invalidfd)
	{
		in = ms_where_is('<', cmd->line);
		out = ms_where_is('>', cmd->line);
		if ((in < out && in != -1) || out == -1)
		{
			if (ms_get_fdin(cmd))
				cmd->invalidfd = 1;
		}
		else if ((out < in && out != -1) || in == -1)
			if (ms_get_fdout(cmd))
				cmd->invalidfd = 1;
	}
}

void	ms_get_fds(t_ms *ms)
{
	int	i;

	i = -1;
	while (++i < ms->nbcmd)
		ms_get_next_fd(&ms->cmd[i]);
}

void	ms_gof_init(int *dels, int *app, int *i, t_cmd *cmd)
{
	*dels = *i - 1;
	*app = 0;
	if (cmd->line[*i] == '>')
	{
		*app = 1;
		(*i)++;
	}
}

int	set_end_filename(t_cmd *cmd, int i)
{
	char	quote;

	if (ms_isquote(cmd->line[i]))
	{
		quote = cmd->line[i++];
		while (cmd->line[i] != quote)
			i++;
	}
	i++;
	return (i);
}
