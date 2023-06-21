/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdjemaa <mdjemaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 16:32:05 by rficht            #+#    #+#             */
/*   Updated: 2023/06/04 15:45:01 by mdjemaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_printcmds(t_ms ms)
{
	int	i;

	i = -1;
	printf("Nb commandes %d\n", ms.nbcmd);
	while (++i < ms.nbcmd)
		ms_printcmd(ms.cmd[i]);
}

/**
 * debug function that print pipes with their respectives in and out.
 * @param ms address of minishell.
 */
void	ms_disp_pipes(t_ms *ms)
{
	int	i;

	i = -1;
	printf("Pipes are :\n");
	while (++i < ms->nbcmd - 1)
		printf("Pipe %d : [0]%d [1]%d\n", i, ms->pipe[i][0], ms->pipe[i][1]);
}

void	ms_printcmd(t_cmd cmd)
{
	printf(YELLOW"commande %d\n"RESET, cmd.nb);
	ft_printstrtab(cmd.args, "ARGS");
	printf("PATH : %s\n", cmd.path);
	printf("CmdName : %s\n", cmd.cmd_name);
	printf("Filein : %s \t fdin %d\n", cmd.filein, cmd.fdin);
	printf("Fileout : %s \t fdout %d\n", cmd.fileout, cmd.fdout);
	printf("Valid fd : %d\n", cmd.invalidfd);
	printf("_____________________________________________\n");
}
