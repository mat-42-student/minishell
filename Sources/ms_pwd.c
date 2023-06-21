/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 09:55:49 by rficht            #+#    #+#             */
/*   Updated: 2023/06/01 08:55:16 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pwd(t_cmd *cmd)
{
	char	buffer[MAXPATHLEN + 1];
	char	*result;

	buffer[MAXPATHLEN] = 0;
	result = getcwd(buffer, MAXPATHLEN);
	if (!result)
		return (1);
	if (ft_putstr_fd(buffer, cmd->fdout) == -1)
		return (1);
	write(cmd->fdout, "\n", 1);
	return (0);
}
