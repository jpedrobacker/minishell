/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:25:23 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/12 13:02:18 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/ft_printf.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <fcntl.h>
# include <errno.h>
# include <limits.h>
# include <unistd.h>
# include <curses.h>
# include <term.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# define WRITE_END 1
# define READ_END 0

typedef struct s_helper
{
	char	*t;
	int		i;
	int		one_q;
	int		two_q;
	int		hd;
}			t_helper;

typedef struct s_varenv
{
	char			*key;
	char			*var;
	struct s_varenv	*next;
	struct s_varenv	*head;
}			t_varenv;

typedef struct s_token
{
	int				fd_in;
	int				fd_out;
	int				pipe_in;
	int				pipe_out;
	int				hd_fd;
	int				hd;
	char			*cmd;
	char			*real_path;
	char			*token;
	char			**arr;
	char			**args;
	pid_t			pid;
	struct s_token	*next;
	struct s_token	*head;
}				t_token;

typedef struct s_main
{
	t_varenv	*envs;
	t_token		*cmds;
	char		**envp;
	char		**splited_pipe;
	char		**paths;
	char		**splited_input;
	char		*dup_usr_input;
	char		*new_input;
	char		*envs_path;
	char		*usr_input;
}			t_main;

enum e_type_of_flags
{
	C = 1,
	P = 2,
	H = 3,
	A = 4,
	I = 5,
	O = 6
};

enum e_type_of_errors
{
	QUOTE = 1,
	NDIR = 2,
	NPERM = 3,
	NCMD = 4,
	DUPERR = 5,
	FORKERR= 6,
	PIPERR = 7,
	PIPENDERR = 8,
	MEM = 9,
	IS_DIR = 10,
	NO_DIR = 11,
	ARGS = 12
};

extern int	g_status;

/*-- redirects functions --*/
int			ordering_fds(t_main *bag);
int			heredoc_func(t_token *node, t_main *bag, int i);
int			exec_redirects(t_token *node, t_main *bag);
int			append_func(t_token *node, t_main *bag, int i);
int			redirect_in(t_token *node, t_main *bag, int i);
int			redirect_out(t_token *node, t_main *bag, int i);

/*-- path functions --*/
char		*find_env_path(t_varenv *envp);
char		*divide_command_input(char *s);
char		*get_real_path(char ***all_paths, char *command);

/*-- Tokenize funcs --*/
void		tokenize(t_main *bag);

/*-- linked list functions --*/
t_token		*create_list(char *usr_input, t_varenv *envs);
t_varenv	*make_envp_list(char **envp);
void		create_node(char *s, t_token **head, char ***paths, t_varenv *envs);
void		link_envp(char *envp, t_varenv *head);

/*-- Validate Input functions --*/
int			validate_input(char *s, t_main *bag);
int			check_invalid_pipe(char *s);
int			check_invalid_redirects(char *s);
int			deal_redirects(t_main *bag);
int			is_appendoc(char *s, int *i, char c);
int			helper_invalid_redis(char *dup, char type, int i);
int			valid_appendoc(char *s, int i, char c);
int			valid_rin_rout(char *s, int i);

/*-- deal quotes functions --*/
void		change_pipe(char *s, int *start, int *end);
void		change_spaces(char *s, int *start, int *end);
int			change_input(char *s);
void		replace_char(char *s, char old, char want);
char		*get_quote_pos(char *s);

/*-- split in tokens --*/
char		**split_in_tokens(char *s, char *in, t_varenv *envs);
int			new_line_count(char *s, char *in, int i);
int			check_char(char *s, int i, int s_len, char *in);
int			check_specials(char *s, int i, int t, char *in);

/*-- expand envs --*/
void		new_expand_envs(char ***matrix, t_varenv *envs);

/*-- builtins --*/
int			our_builtins(char *s);
int			built_cd(t_main *main, t_token *token);
int			built_pwd(t_token *node);
int			built_echo(t_token *token, int flag);
int			built_env(t_main *main, t_token *token);
void		built_exit(t_main *main, t_token *token);
int			built_export(t_varenv *env, t_token *token);
int			built_unset(t_main *main, t_token *token);
int			check_builtins(t_main *main, t_token *token);
void		check_builtins_pipes(t_main *main, t_token *token);

/*-- utils --*/
void		fix_matrix(t_token **head);
void		print_list(t_token **head);
char		*rev_split(char **matrix);
char		*get_cmd(char **arr);
char		**get_args(char **arr);
int			is_there_var(char *s);
int			ft_isvar(char c);
int			count_cmds(char **args);
int			echo_flag(char **args);
int			ft_strcmp(const char *s1, const char *s2);
void		copy_char_pointer(char ***dest, char **src);
void		redir_(t_token *token);
void		close_fds(t_token *token);
void		close_all(t_token *token);
int			ft_isvar(char c);
int			find_char(char *s, char c);

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
void		exec_non_builtin_cmd(t_token *token, char **new_env);
void		exec_normal_cmd_pipe(t_token *token, char **new_env);
void		main_exec(t_main *main);
void		wait_all(t_token *token);
void		exec_cmds_pipe(t_main *main, t_token *token);
void		call_cmd(t_main *main, t_token *token);
int			pre_execute(t_token *token);
int			test_exec(t_token *token);

/*-- env utils --*/
char		*get_env_key(char *envp, char c);
char		*get_env_name(char *s, int flag);
char		*find_var_key(t_varenv *env, char *key_to_find);
int			update_new_pwd(t_varenv *env);
int			update_old_pwd(t_varenv *env);
int			check_var_exist(t_varenv *env, char *input);
int			env_lst_size(t_varenv *env);
void		update_gstatus(t_varenv *env);
char		**linked_to_env(t_varenv *env);

/*-- pipes --*/
int			make_pipe(t_main *bag);
int			if_pipe(t_main *main);

/*-- need to delete --*/
void		print_node(t_main *bag);

/*-- signals --*/
void		sig_int_handle(int sig);
void		sigs_handle(void);

#endif
