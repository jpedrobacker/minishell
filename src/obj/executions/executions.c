/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:00:52 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/01 22:52:05 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exec_normal_cmd_pipe(t_main *main, t_token *token)
{
	t_token	*temp;

	redir_(token);
	temp = main->cmds;
	close_fds(temp);
	execve(token->real_path, token->args, token->envs);
	return ;
}

void	exec_cmds_pipe(t_main *main, t_token *token)
{
	token->pid = fork();
	if (token->pid != 0)
		return ;
	if (!our_builtins(token->cmd))
		exec_normal_cmd_pipe(main, token);
	else
		check_builtins_pipes(main, token);
}

void	exec_non_builtin_cmd(t_token *token)
{
	t_token	*temp;

	token->pid = fork();
	if (token->pid != 0)
		return ;
	redir_(token);
	temp = token;
	close_fds(temp);
	execve(token->real_path, token->args, token->envs);
	return ;
}

void	call_cmd(t_main *main, t_token *token)
{
	token->envs = update_envp(main->envs);
	if (!our_builtins(token->cmd))
		exec_non_builtin_cmd(token);
	else
		check_builtins(main, token);
}

/*
void	call_cmds_pipe(t_main *main)
{
	t_token	*token;
	t_token	*temp;

	token = main->cmds;
	while (token)
	{
		if (!our_builtins(token->cmd))
		{
			token->pid = fork();
			if (token->pid == -1)
			{
				perror("fork");
				exit(1);
			}
			else if (token->pid == 0)
			{
				redir_(token);
				temp = main->cmds;
				close_fds(temp);
				execve(token->real_path, token->args, token->envs);
			}
		}
		else
		{
			check_builtins(main, token);
		}
		token = token->next;
	}
	temp = main->cmds;
	close_fds(temp);
	token = main->cmds;
	while (token)
	{
		wait(NULL);
		token = token->next;
	}
}
*/

/*int	execution(t_main *main)
{
	t_token	*token;

	token = main->cmds;
	while (token)
	{
		ft_printf("CMD: %s, FD_IN: %d, FD_OUT: %d\n", token->cmd, token->fd_in, token->fd_out);
		if (exec_redirects(token, main) != 1)
			return (0);
		call_cmds_pipe(token);
		if (!check_builtins(main))
			call_cmd(main);
		close_all(token);
		token = token->next;
	}

	return (0);
}*/
