/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_utils_01.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rficht <robin.ficht@free.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 09:25:44 by rficht            #+#    #+#             */
/*   Updated: 2023/06/18 14:58:24 by rficht           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_env_var_len(char *var)
{
	int	n;

	n = 0;
	while (ms_env_valid_char(var, n))
		n++;
	return (n + 1);
}

int	ms_env_hasval(char *str)
{
	while (*str)
	{
		if (*str == '=')
			return (TRUE);
		str++;
	}
	return (FALSE);
}

/**
 * Create a copy of envp directclty inside minishell so we can modify it later.
 * Also increase the shlvl. 
 * @param envp The original envp
 * @param ms The addresse of minishell
 */
void	ms_copy_env(char *envp[], t_ms *ms)
{
	char	**envp_copy;
	int		n;

	n = 0;
	envp_copy = ft_calloc(ms_sizeof_tab(envp) + 1, sizeof(char *));
	if (!envp_copy)
		ms_crash(NULL);
	while (envp[n])
	{
		envp_copy[n] = ft_strdup(envp[n]);
		if (!envp_copy[n])
			ms_crash(ms);
		n++;
	}
	ms->envp = envp_copy;
	if (incr_shell_lvl(ms))
		ms_crash(ms);
	ms_exportvar("OLDPWD", ms);
}

void	ms_env_addvar(char *new_var, t_ms *ms)
{
	char	**new_envp;
	int		n;

	n = -1;
	new_envp = ft_calloc(ms_sizeof_tab(ms->envp) + 2, sizeof(char *));
	if (!new_envp)
		ms_crash(ms);
	while (ms->envp[++n])
		new_envp[n] = ms->envp[n];
	new_envp[n] = strdup(new_var);
	free(ms->envp);
	ms->envp = new_envp;
}

/**
 * export a new var into ms_env. Carefull, it doesn't free new var.
 * @param new_var the new variable to export.
 * @param ms a pointer to minishell.
 * @return 0 if succes 1 if fail. 
*/
int	ms_exportvar(char *new_var, t_ms *ms)
{
	int	env_varl;

	if (!ms_valid_name(new_var))
	{
		ft_putstr_fd("msh: export: not a valid identifier\n", 2);
		return (1);
	}
	env_varl = ms_getenv_varl(new_var, ms);
	if (env_varl >= 0)
	{
		free(ms->envp[env_varl]);
		ms->envp[env_varl] = ft_strdup(new_var);
	}
	else
		ms_env_addvar(new_var, ms);
	return (0);
}
