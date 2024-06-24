/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:26:30 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/21 20:06:11 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exec_cmds_pipe(t_token *token, char **env)
{
	if (token->fd_out != STDOUT_FILENO)
		dup2(token->fd_out, STDOUT_FILENO);
	if (token->fd_in != STDIN_FILENO)
		dup2(token->fd_in, STDIN_FILENO);
	token_fds_close(token->head);
	if (execve(token->real_path, token->arr, env) == -1)
	{
		ft_printf("Command not found!\n");
		exit(127);
	}
	return ;
}

void	call_cmds_pipe(t_token *token)
{
	token->pid = fork();
	if (token->pid == 0)
		exec_cmds_pipe(token, token->envs);
	return ;
}

void	close_all(t_token *token)
{
	while (token && token->flag != P)
	{
		if (token->fd_in != STDIN_FILENO)
			close(token->fd_in);
		if (token->fd_out != STDOUT_FILENO)
			close(token->fd_out);
		token = token->next;
	}
	return ;
}

int	execution(t_main *main)
{
	t_token	*token;

	token = main->cmds;
	make_pipe(token);
	while (token)
	{
		if (1)
			call_cmds_pipe(token);
		if (!check_builtins(main))
			call_cmd(main);
		close_all(token);
		token = token->next;
	}
	return (0);
}

void	start_execution(char *usr_input, t_main *main)
{
	(void) usr_input;
	main->new_input = rev_split(main->splited_input);
	tokenize(main);
	execution(main);
	//waitpid dos comandos
	//free do token
}

