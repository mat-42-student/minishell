/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 11:14:32 by rficht            #+#    #+#             */
/*   Updated: 2023/06/15 09:53:43 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(char **str_tab, int fd)
{
	while (*str_tab)
	{
		ft_putstr_fd(*str_tab, fd);
		write(fd, "\n", 1);
		str_tab++;
	}
}

int	env_addquotes(char **str)
{
	int	n;

	n = 0;
	while ((*str)[n])
	{
		if ((*str)[n++] == '=')
		{
			if (ft_strinsert(str, "\"", n))
				return (1);
			break ;
		}
	}
	while ((*str)[n])
		n++;
	if (ft_strinsert(str, "\"", n))
		return (1);
	return (0);
}

int	format_tab(char **str_tab)
{
	int	n;

	n = 0;
	while (str_tab[n])
	{
		if (ft_strinsert(&str_tab[n], "declare -x ", 0))
			return (1);
		if (ms_env_hasval(str_tab[n]))
		{
			if (env_addquotes(&str_tab[n]))
				return (1);
		}
		n++;
	}
	return (0);
}

void	sort_tab(char **str_tab)
{
	int		is_finished;
	char	*tmp;
	int		n;

	is_finished = 0;
	while (!is_finished)
	{
		is_finished = 1;
		n = 0;
		while (str_tab[n] && str_tab[n + 1])
		{
			if (ft_strcmp(str_tab[n], str_tab [n + 1]) > 0)
			{
				tmp = str_tab[n];
				str_tab[n] = str_tab[n + 1];
				str_tab[n + 1] = tmp;
				is_finished = 0;
			}
			n++;
		}
	}
}

void	ms_no_arg_export(t_ms *ms, int fd_out)
{
	char	**envp_copy;
	int		n;

	envp_copy = ft_calloc(ms_sizeof_tab(ms->envp) + 1, sizeof(char *));
	if (!envp_copy)
	{
		printf("ms_no_arg_export failed to malloc\n");
		return ;
	}
	n = -1;
	while (ms->envp[++n])
		envp_copy[n] = ft_strdup(ms->envp[n]);
	sort_tab(envp_copy);
	format_tab(envp_copy);
	print_export(envp_copy, fd_out);
	ft_freetab(envp_copy);
	envp_copy = NULL;
}
