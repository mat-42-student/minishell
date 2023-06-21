/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamat <mamat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:32:55 by mdjemaa           #+#    #+#             */
/*   Updated: 2023/06/20 00:58:22 by mamat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/param.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <term.h>
# include <unistd.h>
# include "libft.h"

# define FALSE	0
# define TRUE	1
# define SYN_EUNEXT "msh : syntax error near unexpected token "
# define SPACES "\t\n\v\f\r "
# define END_REDIR " #<>\0"
# define FORBID_REDIR "#<>|"
# define END_HEREDOC " #<>|\0"
# define FORBID_HEREDOC "#<>|"
# define FORBID_CHAR "\\;()[]&"
# define NO_F ": No such file or directory\n"

typedef struct s_cmd	t_cmd;
typedef struct s_export	t_export;

/**
 * @param normal default mode
 * @param prompt mode when entering text
 * @param child mode to quit inside child
 * @param disabled mode that totally disable signals when calling a child
 */
typedef enum e_sig
{
	normal,
	prompt,
	child,
	disabled
}	t_sig;

typedef struct s_ms
{
	char	*rl_str;
	char	**envp;
	int		histofd;
	int		term_fd;
	char	*line;
	int		nbcmd;
	int		**pipe;
	pid_t	*pid;
	t_cmd	*cmd;
}	t_ms;

struct s_cmd
{
	char	*line;
	int		nb;
	char	*limiter;
	char	*filein;
	char	*fileout;
	int		*herepipe;
	int		fdin;
	int		fdout;
	int		invalidfd;
	char	*cmd_name;
	char	**args;
	char	*path;
	t_ms	*ms;
};

struct s_export
{
	int		add;
	char	*name;
	char	*value;
};

//init
void	line_init(char	*str, t_ms *p);

//err and memory
void	ms_crash(t_ms *ms);
void	ms_free_cmd(t_ms *ms);
void	ms_free(t_ms *ms);
void	ms_free_env(t_ms *ms);
int		ms_error_msg(char *str, int err);
int		ms_exit_dir(char *str);
int		ms_error_file(char *file, char m, int err);
void	ms_bad_child_ending(char *pathcmd);
void	ms_loop_free(t_ms *ms);

//parsing
int		ms_get_cmds(t_ms *ms);
char	*ms_trim_hashtag(char *str);
int		ms_isquote(char c);
int		*ms_where_are(char c, char *str);
int		ms_where_is(char c, char *str);
int		ms_where_is_last(char c, char *str);
int		ms_quote_status(char *str, int j);
char	**ms_quotesplit(char *s, char sep, t_ms *ms);
char	*ms_noquotes(char *str);
int		ms_checkpipes(char *str);
int		ms_badchev(char *str);
int		ms_pipesplit(t_ms *ms);
int		ms_trimquotes(char **str);
int		ms_wrongchars(char	*str);

// redirection
void	ms_get_fds(t_ms *ms);
int		ms_get_fdin(t_cmd *cmd);
int		ms_get_fdout(t_cmd *cmd);
int		ms_getinfile(t_cmd *cmd, int i);
int		ms_get_limiter(t_cmd *cmd, int i);
void	ms_gof_init(int *dels, int *app, int *i, t_cmd *cmd);
int		ms_heredoc(t_cmd *cmd);
void	ms_openfile(t_cmd *cmd, char *file, char m);
int		set_end_filename(t_cmd *cmd, int i);

//lexing & execution
int		ms_isbuiltin(char *str);
int		ms_lex(t_ms *ms);
int		ms_exec(t_ms *ms);
int		ms_launch_children(t_ms *ms);
int		ms_close(t_ms *ms, int val);

//terminal
int		ms_terminal_init(t_ms *ms);
int		ms_terminal_reset(t_ms *ms);

//builtins
int		ms_cd(t_cmd *cmd);
int		ms_exit(t_cmd *cmd);
int		ms_env(t_cmd *cmd);
int		ms_unset(t_cmd *cmd);
int		ms_echo(t_cmd *cmd);
int		ms_export(t_cmd *cmd);
int		ms_pwd(t_cmd *cmd);

// exec
int		ms_do_builtin(t_cmd	*cmd);
void	ms_fixfds(t_cmd	*cmd);
void	ms_close_pipes_but(t_ms *ms, int i);
int		ms_is_localfile(char *file);
int		ms_check_fds(t_cmd cmd);
void	ms_exit_check_fds(t_cmd cmd);

//utils
int		ms_dollar_replace(char **str, t_ms *ms);
void	set_sig(void);
int		ms_sizeof_tab(char **my_tab);
int		incr_shell_lvl(t_ms *ms);
int		ms_env_pos(char *str, char **envp);
void	ms_copy_env(char *envp[], t_ms *ms);
char	*ms_getenv_val(char *str, t_ms *ms);
int		ms_getenv_varl(char *str, t_ms *ms);
int		ms_env_valid_char(char *str, int pos);
int		is_env(char *str, char *env);
int		ms_env_var_len(char *str);
void	ms_no_arg_export(t_ms *ms, int fd_out);
int		ms_env_hasval(char *str);
int		ms_exportvar(char *new_var, t_ms *ms);
int		ms_exp_exportvar(t_export *exp, t_ms *ms);
int		ms_valid_name(char *new_var);
void	ms_exp_free(t_export *exp, int max);
int		ms_exp_all(t_export *exp, t_ms *ms, int max);

//debug
void	ms_printtab(char **str_tab, int fd);
void	ms_printcmds(t_ms ms);
void	ms_printcmd(t_cmd cmd);
void	ms_disp_pipes(t_ms *ms);
void	ms_printcmd(t_cmd cmd);

//statics
int		stat_sig(int val);
int		stat_err(int val);

//doll replacing
int		dol_replace(char **str, int pos, t_ms *ms);
int		is_doll_replaced(char *str, int n);
int		ms_trim_empty_dolls(char **str, t_ms *ms);

#endif