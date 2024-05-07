/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:25:23 by jbergfel          #+#    #+#             */
/*   Updated: 2024/05/07 12:42:04 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include "../lib/ft_printf.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <linux/limits.h>

typedef struct	s_token
{
	int			fd_in;
	int			fd_out;
	char		*real_path;
	char		*command;
	char		*command_input;
	char		**env_path;
	char		**arr_command;
	struct s_token	*next;
}			t_token;

/*-- path functions --*/
char	*find_env_path(char **envp);
char	*divide_command_input(char *s);
char	*get_real_path(char ***all_paths, char *command);

/*-- linked list functions --*/
void	create_node(char *s, t_token **head, char ***paths);
void	create_list(char *usr_input, char **envp);

/*-- utils --*/
void	print_list(t_token **head);

/*-- builtins --*/
int		built_cd(char *arg);
int		built_echo(char *str, char *flag);
int		built_pwd(void);
void	built_env(char **envp);
void	built_exit(void);

#endif
