/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing_00.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:20:11 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/06/18 11:26:50 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * return TRUE or FALSE depending on whether quotes are closed or not.
 * @param str line of commande after spaces have been trimed.
 */
int	ms_openquotes(char *str)
{
	int		open;
	int		i;
	char	quote;

	i = -1;
	open = FALSE;
	if (!str)
		return (-1);
	while (str[++i])
	{
		if (!open && ms_isquote(str[i]))
		{
			quote = str[i];
			open = TRUE;
		}
		else if (str[i] == quote)
			open = FALSE;
	}
	return (open);
}

/**
 * return TRUE or FALSE depending on whether the line is valid or not.
 * @param str line of commande after spaces have been trimed.
 */
int	ms_syntax_ok(char *str)
{
	if (ms_openquotes(str))
		return (ms_error_msg("msh : no matching `\"\' ", FALSE));
	if (ms_wrongchars(str))
		return (FALSE);
	return (TRUE);
}

/**
 * Allocates memory for pipes and init them with pipe().
 * @param ms address of minishell.
 * @return always return 0 (unexpected working calls ms_crash).
 */
int	ms_pipe_init(t_ms *ms)
{
	int	i;

	if (ms->nbcmd < 2)
	{
		ms->pipe = 0;
		return (0);
	}
	ms->pipe = ft_calloc((ms->nbcmd - 1), sizeof(int *));
	if (!ms->pipe)
		ms_crash(ms);
	i = -1;
	while (++i < ms->nbcmd - 1)
	{
		ms->pipe[i] = malloc(2 * sizeof(int));
		if (!ms->pipe[i] || pipe(ms->pipe[i]) == -1)
			ms_crash(ms);
	}
	return (0);
}

/**
 * Separate the str line based on the | symboles.
 * @param ms address of minishell.
 * @return return 0 in case of success otherwise return 1.
 */
int	ms_cmds_init(t_ms *ms)
{
	int	i;

	i = -1;
	ms->nbcmd = ms_pipesplit(ms);
	if (ms->nbcmd == -1)
		return (1);
	while (++i < ms->nbcmd)
	{
		ms->cmd[i].nb = i;
		ms->cmd[i].args = 0;
		ms->cmd[i].cmd_name = 0;
		ms->cmd[i].fdin = 0;
		ms->cmd[i].filein = 0;
		ms->cmd[i].fileout = 0;
		ms->cmd[i].fdout = 1;
		ms->cmd[i].limiter = 0;
		ms->cmd[i].herepipe = 0;
		ms->cmd[i].invalidfd = 0;
		ms->cmd[i].path = 0;
		ms->cmd[i].ms = ms;
	}
	ms_pipe_init(ms);
	return (0);
}

/**
 * verify if the line is valid or not turn the line into an array of struct cmd.
 * set err val. Alloc errors calls exit(). 
 * @param ms address of minishell.
 * @return return TRUE or FALSE depending on whether the line is valid or not.
 */
int	ms_get_cmds(t_ms *ms)
{
	if (ft_strequal(ms->line, ""))
	{
		ms->nbcmd = 0;
		return (FALSE);
	}
	if (!ms_syntax_ok(ms->line))
	{
		stat_err(258);
		return (FALSE);
	}
	if (ms_cmds_init(ms))
		return (FALSE);
	return (TRUE);
}
