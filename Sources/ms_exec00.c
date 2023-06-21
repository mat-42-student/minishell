/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamat <mamat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 20:28:47 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/06/20 01:06:29 by mamat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_isbuiltin(char *str)
{
	if (ft_strequal(str, "cd"))
		return (1);
	if (ft_strequal(str, "echo"))
		return (1);
	if (ft_strequal(str, "env"))
		return (1);
	if (ft_strequal(str, "exit"))
		return (1);
	if (ft_strequal(str, "export"))
		return (1);
	if (ft_strequal(str, "pwd"))
		return (1);
	if (ft_strequal(str, "unset"))
		return (1);
	return (0);
}

void	ms_close_pipes_but(t_ms *ms, int i)
{
	int	j;

	j = -1;
	while (++j < ms->nbcmd - 1)
	{
		if (j != i - 1)
			close(ms->pipe[j][0]);
		if (j != i)
			close(ms->pipe[j][1]);
	}
}

// int	ms_is_localfile(char *file)
// {
// 	return (file[0] == '.' && file[1] == '/');
// }

int	ms_exit_fd(t_cmd cmd)
{
	if (cmd.fdin == -1)
	{
		if (access(cmd.filein, F_OK) == -1)
			return (ms_error_file(cmd.filein, 'r', 1));
		if (access(cmd.filein, R_OK) == -1)
			return (ms_error_file(cmd.filein, 'r', 1));
	}
	if (cmd.fdout == -1)
	{
		if (access(cmd.fileout, F_OK) == -1)
			return (ms_error_file(cmd.fileout, 'w', 1));
		if (access(cmd.fileout, W_OK) == -1)
			return (ms_error_file(cmd.fileout, 'w', 1));
	}
	return (1);
}

void	ms_exit_check_fds(t_cmd cmd)
{
	int	err;

	err = ms_check_fds(cmd);
	if (err)
		exit(err);
}

int	ms_check_fds(t_cmd cmd)
{
	if (cmd.invalidfd)
		return (ms_exit_fd(cmd));
	return (0);
}
