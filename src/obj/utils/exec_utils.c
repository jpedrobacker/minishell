/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:44:10 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/10 14:42:39 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	if_pipe(t_main *main)
{
	t_token *token;
	int		i;

	i = 0;
	token = main->cmds;
	while (token)
	{
		i++;
		token = token->next;
	}
	if (i == 1)
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
