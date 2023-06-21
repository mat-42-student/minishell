/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamat <mamat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:23:24 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/06/20 01:22:39 by mamat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ms_getpath(t_ms *ms)
{
	int		i;

	i = -1;
	while (ms->envp[++i])
		if (ft_strnstr(ms->envp[i], "PATH=", 5))
			return (ms_quotesplit(ms->envp[i] + 5, ':', ms));
	return (0);
}

char	*ms_findpath(char *cmd, char **path)
{
	char	*fullcmd;

	if (!cmd || ft_strequal(cmd, ""))
		return (0);
	while (path && *path)
	{
		fullcmd = ft_strmanyjoin(*path, "/", cmd, 0);
		if (!access(fullcmd, F_OK | X_OK))
		{
			ft_freestr(&fullcmd);
			return (ft_strjoin(*path, "/"));
		}
		ft_freestr(&fullcmd);
		path++;
	}
	return (0);
}

int	ms_dealwith_quotes_and_dols(t_cmd *cmd)
{
	int	i;
	int	err;

	err = 0;
	i = -1;
	while (cmd->args[++i])
	{
		if (!ms_dollar_replace(&cmd->args[i], cmd->ms))
			ms_trimquotes(&cmd->args[i]);
		else
			err = 1;
	}
	return (err);
}

int	ms_get_path_from_name(t_ms *ms, int i)
{
	int		pos;
	char	*tmp;

	pos = ms_where_is_last('/', ms->cmd[i].cmd_name);
	ms->cmd[i].path = ft_substr(ms->cmd[i].cmd_name, 0, pos + 1);
	tmp = ft_substr(ms->cmd[i].cmd_name, pos + 1, \
		ft_sstrlen(ms->cmd[i].cmd_name) - pos);
	ft_freestr(&ms->cmd[i].cmd_name);
	ms->cmd[i].cmd_name = tmp;
	return (0);
}

/**
 * will turn lines into an arg array to conform with c program syntax.
 * It will first split with spcaces, replace dollars and remove quotes.
 * @param ms ptr om minishell
 * @return 0 if successful and 1 if fail
 * 
 */
int	ms_lex(t_ms *ms)
{
	int		i;
	char	**path;

	i = -1;
	while (++i < ms->nbcmd)
	{
		ms_trim_empty_dolls(&ms->cmd[i].line, ms);
		ms->cmd[i].args = ms_quotesplit(ms->cmd[i].line, ' ', ms);
		if (ms->cmd[i].args)
		{
			ms_dealwith_quotes_and_dols(&ms->cmd[i]);
			ms->cmd[i].cmd_name = ft_strdup(ms->cmd[i].args[0]);
		}
		else
			return (1);
		if (ms_where_is('/', ms->cmd[i].cmd_name) != -1)
			return (ms_get_path_from_name(ms, i));
		path = ms_getpath(ms);
		ms->cmd[i].path = ms_findpath(ms->cmd[i].cmd_name, path);
		ft_freetab(path);
	}
	return (0);
}
