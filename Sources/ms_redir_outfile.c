/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir_outfile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 17:08:47 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/06/16 17:38:36 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_getoutfile(t_cmd *cmd, int i)
{
	int		delstart;
	int		start;
	int		append;

	ms_gof_init(&delstart, &append, &i, cmd);
	while (cmd->line[i] == ' ')
		i++;
	if (cmd->line[i] && ft_is_in(cmd->line[i], FORBID_REDIR) >= 0)
		return (ms_error_msg(SYN_EUNEXT">", 1));
	start = i;
	while (cmd->line[i] && ft_is_in(cmd->line[i], END_REDIR) == -1)
		i = set_end_filename(cmd, i);
	cmd->fileout = ft_substr(cmd->line, start, i - start);
	if (!cmd->fileout)
		ms_crash(cmd->ms);
	if (ms_dollar_replace(&cmd->fileout, cmd->ms))
		return (1);
	ms_trimquotes(&cmd->fileout);
	if (append)
		cmd->fdout = open(cmd->fileout, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		cmd->fdout = open(cmd->fileout, O_CREAT | O_RDWR | O_TRUNC, 0644);
	ft_strdelnfrom(&cmd->line, delstart, i - delstart);
	return (0);
}

/**
 * Verify the outfile is valid and interpret it into a Filedescriptor.
 * @param cmd a cmd struct.
 * @return return 0 or 1 whether the format of filein is valid or not.
 */
int	ms_get_fdout(t_cmd *cmd)
{
	int	i;

	i = ms_where_is('>', cmd->line);
	if (cmd->fileout)
		ft_freenull((void **)&cmd->fileout);
	if (ms_getoutfile(cmd, i + 1) || cmd->fdout == -1)
		return (1);
	return (0);
}
