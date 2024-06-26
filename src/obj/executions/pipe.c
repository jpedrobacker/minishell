/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:11:49 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/25 21:11:11 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	make_pipe(t_token *token)
{
	int		fd[2];
	t_token	*cmds;

	while(token)
	{
		cmds = token;
		/*while (token && token->flag != P)
			token = token->next*/
		token = token->next; //temporario
		if (!token)
			return (0);
		if (pipe(fd) == -1)
			return (1);
		cmds->fd_out = fd[1];
		token = token->next;
		cmds = token;
		if (cmds)
			cmds->fd_in = fd[0];
		else
		{
			close(fd[0]);
			close(fd[1]);
		}
	}
	return (0);
}

void	close_fds(t_token *token)
{
	while (token)
	{
		if (token->fd_in != STDIN_FILENO)
			close(token->fd_in);
		else if (token->fd_out != STDOUT_FILENO)
			close(token->fd_out);
		token = token->next;
	}
	return ;
}

void	exec_cmds_pipe(t_token *token, char **envp)
{
	if (!token)
	if (token->fd_out != STDOUT_FILENO)
		dup2(token->fd_out, STDOUT_FILENO);
	if (token->fd_in != STDIN_FILENO)
		dup2(token->fd_in, STDIN_FILENO);
	close_fds(token);
	if (execve(token->real_path, token->arr, envp) == -1)
	{
		ft_putstr_fd("Command not found\n", 2);
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
