/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:44:10 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/02 20:40:02 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	if_pipe(t_main *main)
{
	t_token *token;

	token = main->cmds;
	if (token->next != NULL)
		return (1);
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

void	redir_(t_token *token)
{
	if (token->fd_in != STDIN_FILENO)
		dup2(token->fd_in, STDIN_FILENO);
	if (token->fd_out != STDOUT_FILENO)
		dup2(token->fd_out, STDOUT_FILENO);
}

void	close_all(t_token *token)
{
	if (token->fd_in != STDIN_FILENO)
		close(token->fd_in);
	if (token->fd_out != STDOUT_FILENO)
		close(token->fd_out);
	return ;
}

void	wait_all(t_token *token)
{
	t_token	*aux;
	extern int	g_status;
	int	status;

	status = 0;
	if (!token)
		return ;
	aux = token;
	while (token)
	{
		if (token->pid != 0)
			waitpid(token->pid, &status, 0);
		token = token->next;
	}
	token = aux;
	while (token)
	{
		if (status >= 0)
			g_status = WEXITSTATUS(status);
		token = token->next;
	}
	return ;
}
