/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:25:23 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/19 21:42:46 by aprado           ###   ########.fr       */
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
	char			*full_env; //malloc
	char			*key;
	char			*var; //malloc
	struct s_varenv	*next;
	struct s_varenv	*head;
}			t_varenv;

typedef struct	s_token
{
	int				fd_in;
	int				fd_out;
	char			*real_path;
	char			*token;
	char			**arr;
	char			**envs;
	pid_t			pid;
	struct s_token	*next;
	struct s_token	*head;
}				t_token;

typedef struct		s_main
{
	t_varenv	*envs;
	t_token		*cmds;
	char		**envp; //malloc
	char		**splited_pipe;
	char		**paths;
	char		**splited_input;
	char		*dup_usr_input;
	char		*new_input;
	char		*envs_path;
}			t_main;

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

/*
enum e_flags
{
	C = 1, // Command
	P = 2, // Command + Pipe
	H = 3, // Heredoc
	A = 4, // Append
	I = 5, // Redirect input
	O = 6, // Redirect output
}
*/

/*-- redirects functions --*/
void	check_redirects(t_main *bag);
void	exec_redirects(t_token *node);

/*-- path functions --*/
char		*find_env_path(t_varenv *envp);
char		*divide_command_input(char *s);
char		*get_real_path(char ***all_paths, char *command);

/*-- Tokenize funcs --*/
void	tokenize(t_main *bag);

/*-- linked list functions --*/
t_token		*create_list(char *usr_input, t_varenv *envs);
t_varenv	*make_envp_list(char **envp);
void		create_node(char *s, t_token **head, char ***paths, t_varenv *envs);
void		link_envp(char *envp, t_varenv **head);

/*-- Validate Input functions --*/
int			validate_input(char *s, t_main *bag);
int			check_invalid_pipe(char *s);
int			check_invalid_redirects(char *s);
int			deal_redirects(t_main *bag);

/*-- deal quotes functions --*/
void		change_pipe(char *s, int *start, int *end);
void		change_spaces(char *s, int *start, int *end);
void		change_input(char *s);
void		replace_char(char *s, char old, char want);
char		*get_quote_pos(char *s);

/*-- split in tokens --*/
char		**split_in_tokens(char *s, char *in, t_varenv *envs);
int			line_count(char *s, char *in, int s_len);
int			check_char(char *s, int i, int s_len, char *in);

/*-- expand envs --*/
void		expand_envs(char ***matrix, t_varenv *envs);
void		new_expand_envs(char ***matrix, t_varenv *envs);

/*-- builtins --*/
int			built_cd(t_main **main);
int			built_pwd(void);
int			built_echo(t_main **main, int flag);
int			built_env(t_main **main);
void		built_exit(t_main *main);
int			built_export(t_main **main);
int			built_unset(t_main *main);
int			built_clear(void);
int			check_builtins(t_main *main);

/*-- utils --*/
void		fix_matrix(t_token **head);
void		print_list(t_token **head);
char		*rev_split(char **matrix);
int			is_there_var(char *s);
int			count_cmds(char **args);
int			echo_flag(char **args);
int			ft_strcmp(const char *s1, const char *s2);
void		copy_char_pointer(char ***dest, char **src);

/*-- handle errors --*/
void		*errors_mini(int type_err, char *param);
void		to_free_token(t_token **token);
void		to_free_varenv(t_varenv **lst_env);
void		free_splits(char **split);
void		free_all(t_main *bag);
void		envs_free(t_varenv **head);
void		token_free(t_token **head);

/*-- exec functions --*/
void		start_execution(char *usr_input, t_main *main);
void		token_fds_close(t_token *head);
void		exec_non_builtin_cmd(t_token *token, char **env);
int			call_cmd(t_main *main);

/*-- env utils --*/
char		*get_env_key(char *envp, char c);
char		*get_env_name(char *s, int flag, int s_len);
char		**update_envp(t_varenv *env);
char		*find_var_key(t_varenv **env, char *key_to_find);
int			update_new_pwd(t_varenv **env);
int			update_old_pwd(t_varenv **env);
int			check_var_exist(t_varenv **env, char *input);
int			env_lst_size(t_varenv *env);

#endif
