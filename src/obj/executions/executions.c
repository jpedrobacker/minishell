/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:00:52 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/09 10:37:24 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exec_normal_cmd_pipe(t_token *token)
{
//	t_token	*temp;
	redir_(token);
//	temp = token;
//	close_fds(temp);
	execve(token->real_path, token->args, NULL);
	return ;
}

void	exec_cmds_pipe(t_main *main, t_token *token)
{
	token->pid = fork();
	if (token->pid != 0)
		return ;
	if (!our_builtins(token->cmd))
		exec_normal_cmd_pipe(token);
	else
		check_builtins_pipes(main, token);
}

void	exec_non_builtin_cmd(t_token *token)
{
	//t_token	*temp;
	token->pid = fork();
	if (token->pid != 0)
		return ;
	redir_(token);
	//temp = token;
	//close_fds(temp);
	execve(token->real_path, token->args, NULL);
	return ;
}

void	call_cmd(t_main *main, t_token *token)
{
	if (!our_builtins(token->cmd))
		exec_non_builtin_cmd(token);
	else
		check_builtins(main, token);
}
