/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:25:23 by jbergfel          #+#    #+#             */
/*   Updated: 2024/05/28 13:32:06 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/ft_printf.h"
# include "colors.h"
# include <stdio.h>				// para printf
# include <stdlib.h>			// para malloc, free, exit
# include <unistd.h>			// para write, access, fork, wait, waitpid, wait3, wait4, execve, dup, dup2, pipe, getcwd, chdir, stat, lstat, fstat, unlink, getpid
# include <signal.h>			// para signal, sigaction, sigemptyset, sigaddset, kill
# include <dirent.h>			// para opendir, readdir, closedir
# include <string.h>			// para strerror, perror
# include <termios.h>			// para tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <fcntl.h>				// para open
# include <errno.h>				// para perror
# include <limits.h>			// para PATH_MAX
# include <unistd.h>			// para isatty, ttyname, ttyslot
# include <curses.h>			// para tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <term.h>				// para tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <fcntl.h>				// para open, close
# include <sys/types.h>			// para tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <sys/stat.h>			// para stat, lstat, fstat
# include <sys/ioctl.h>			// para ioctl
# include <sys/wait.h>			// para waitpid
# include <readline/readline.h>	// para readline
# include <readline/history.h>	// para add_history, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay

typedef struct s_varenv
{
	char			*key;
	char			*var;
	struct s_varenv	*next;
}			t_varenv;

typedef struct s_token
{
	int				fd_in;
	int				fd_out;
	int				flag_expand;
	char			*expanded_env;
	char			*real_path;
	char			*cmd_name;
	char			*cmd_input;
	char			**arr_cmd_input;
	char			*env;
	t_varenv		*envs_lst;
	struct s_token	*next;
}			t_token;

enum e_type_of_errors
{
	QUOTE = 1, //Looking for matching quote
	NDIR = 2, //No such file or dir
	NPERM = 3, //Permission denied
	NCMD = 4, //Command not found
	DUPERR = 5, //dup2 failed
	FORKERR= 6, //fork failed
	PIPERR = 7,//error creating pipe
	PIPENDERR = 8, //syntax error near unexpected toke '|'
	MEM = 9, //no memory left on device
	IS_DIR = 10, //Is a dir
	NO_DIR = 11, //Not a
	ARGS = 12 //Too many arguments
};

/*-- path functions --*/
char		*find_env_path(char **envp);
char		*divide_command_input(char *s);
char		*get_real_path(char ***all_paths, char *command);

/*-- linked list functions --*/
void		create_node(char *s, t_token **head, char ***paths, t_varenv *envs);
t_token		*create_list(char *usr_input, char **envp, t_varenv *envs);
t_varenv	*make_envp_list(char **envp);
void		link_envp(char *envp, t_varenv **head);

/*-- deal quotes functions --*/
void		change_pipe(char *s, int *start, int *end);
void		change_spaces(char *s, int *start, int *end);
char		*get_quote_pos(char *s);
void		change_input(char *s);
void		replace_char(char *s, char old, char want);

/*-- utils --*/
void		fix_matrix(t_token **head);
void		print_list(t_token **head);
int			is_there_var(char *s);
char		*get_env_name(char *s);
char		*get_env_key(char *envp, char c);
int			count_cmds(char **args);
int			echo_flag(char **args);

/*-- builtins --*/
int			built_cd(t_token **token);
int			built_pwd(void);
void		built_echo(t_token **token, int flag);
void		built_env(t_varenv **envp, t_token **token);
void		built_exit(t_varenv *env, t_token *token);
void		built_export(t_varenv **env, t_token **token);
void		built_unset(t_varenv **env, t_token **token);
void		built_clear(void);
void		call_cmd(t_token *token, t_varenv *envp);

/*-- handle errors --*/
void		*errors_mini(int type_err, char *param);
void		to_free_token(t_token **token);
void		to_free_varenv(t_varenv **lst_env);
void		free_splits(char **split);

#endif
