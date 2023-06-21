/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir_infile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:54:53 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/06/16 17:36:59 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Verify the infile is valid and interpret it into a Filedescriptor.
 * @param cmd a cmd struct.
 * @return return 0 or 1 whether the format of filein is valid or not.
 */
int	ms_get_fdin(t_cmd *cmd)
{
	int	i;

	i = ms_where_is('<', cmd->line);
	if (cmd->limiter)
		ft_freestr(&cmd->limiter);
	if (cmd->filein)
		ft_freenull((void **)&cmd->filein);
	if (cmd->line[i + 1] == '<')
	{
		if (ms_get_limiter(cmd, i + 2))
			return (1);
		if (ms_heredoc(cmd))
			return (1);
	}
	else
		if (ms_getinfile(cmd, i + 1) || cmd->fdin == -1)
			return (1);
	return (0);
}

int	ms_getinfile(t_cmd *cmd, int i)
{
	int		delstart;
	int		start;

	delstart = i - 1;
	while (cmd->line[i] == ' ')
		i++;
	if (cmd->line[i] && ft_is_in(cmd->line[i], FORBID_REDIR) >= 0)
		return (ms_error_msg(SYN_EUNEXT"<", 1));
	start = i;
	while (cmd->line[i] && ft_is_in(cmd->line[i], END_REDIR) == -1)
		i = set_end_filename(cmd, i);
	cmd->filein = ft_substr(cmd->line, start, i - start);
	ft_strdelnfrom(&cmd->line, delstart, i - delstart);
	if (ms_dollar_replace(&cmd->filein, cmd->ms))
		return (1);
	ms_trimquotes(&cmd->filein);
	cmd->fdin = open(cmd->filein, O_RDONLY);
	return (0);
}

/**
 * define the liniter if we encounter a << symbol.
 * @param cmd a struct cmd.
 * @param i index of char after the << symbol.
 * @return return 0 or 1 or whether if the Heredoc is valid or not. 
 */
int	ms_get_limiter(t_cmd *cmd, int i)
{
	int	delstart;
	int	start;

	delstart = i - 2;
	while (cmd->line[i] == ' ')
		i++;
	start = i;
	if (ft_is_in(cmd->line[i], FORBID_HEREDOC) >= 0)
		return (1);
	while (cmd->line[i] && ft_is_in(cmd->line[i], END_HEREDOC) == -1)
		i++;
	cmd->limiter = ft_substr(cmd->line, start, i - start);
	if (!cmd->limiter || !cmd->line)
		ms_crash(cmd->ms);
	ft_strdelnfrom(&cmd->line, delstart, i - delstart);
	ms_trimquotes(&cmd->limiter);
	if (!cmd->limiter)
		ms_crash(cmd->ms);
	return (0);
}

void	ms_heredoc_child(t_cmd *cmd)
{
	char	*str;

	stat_sig(child);
	str = readline(">");
	while (!ft_strequal(cmd->limiter, str) && str)
	{
		if (!ms_dollar_replace(&str, cmd->ms))
		{
			write(cmd->herepipe[1], str, ft_sstrlen(str));
			write(cmd->herepipe[1], "\n", 1);
		}
		free(str);
		str = readline(">");
	}
	close(cmd->herepipe[1]);
	exit(0);
}

int	ms_heredoc(t_cmd *cmd)
{
	int		pid;
	int		err;

	err = 0;
	cmd->herepipe = malloc(2 * sizeof(int));
	if (!cmd->herepipe || pipe(cmd->herepipe) == -1)
		return (1);
	stat_sig(disabled);
	pid = fork();
	if (!pid)
		ms_heredoc_child(cmd);
	waitpid(pid, &err, 0);
	stat_sig(normal);
	close(cmd->herepipe[1]);
	cmd->fdin = cmd->herepipe[0];
	ft_freestr(&cmd->limiter);
	free(cmd->herepipe);
	return (WEXITSTATUS(err));
}
