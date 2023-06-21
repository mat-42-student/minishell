/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deprecated_terminal.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:53:41 by rficht            #+#    #+#             */
/*   Updated: 2023/06/01 08:55:16 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	ms_terminal_reset(t_ms *ms)
{
	if (ms->term_fd != -1)
	{
		if (tcsetattr(ms->term_fd, TCSANOW, &ms->term_original))
			return (errno = ENOTSUP);
	}
	return (errno = 0);
}

int	ms_terminal_init(t_ms *ms)
{
	ms->goon = 1;
	ms->pipe = 0;
	if (ms->term_fd != -1)
		return (errno = 0);
	if (isatty(STDERR_FILENO))
		ms->term_fd = STDERR_FILENO;
	else if (isatty(STDIN_FILENO))
		ms->term_fd = STDIN_FILENO;
	else if (isatty(STDOUT_FILENO))
		ms->term_fd = STDOUT_FILENO;
	else
		return (errno = ENOTTY);
	if (tcgetattr(ms->term_fd, &ms->term_original)
		|| tcgetattr(ms->term_fd, &ms->term_settings))
		return (errno = ENOTSUP);
	tcsetattr(ms->term_fd, TCSANOW, &ms->term_settings);
	return (errno = 0);
}*/
