/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:00:52 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/11 16:39:47 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exec_normal_cmd_pipe(t_token *token, char **new_env)
{
	t_token	*temp;

	redir_(token);
	temp = token;
	close_fds(temp);
	execve(token->real_path, token->args, new_env);
	return ;
}

void	exec_cmds_pipe(t_main *main, t_token *token)
{
	char	**new_env;

	token->pid = fork();
	if (token->pid != 0)
		return ;
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (!our_builtins(token->cmd))
	{
		new_env = linked_to_env(main->envs);
		exec_normal_cmd_pipe(token, new_env);
		free_splits(new_env);
	}
	else
	{
		check_builtins(main, token);
		free_all(main);
		envs_free(&main->envs);
		token_free(&main->cmds);
		exit(g_status);
	}
}

void	exec_non_builtin_cmd(t_token *token, char **new_env)
{
	t_token	*temp;

	token->pid = fork();
	if (token->pid != 0)
		return ;
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	redir_(token);
	temp = token;
	close_fds(temp);
	execve(token->real_path, token->args, new_env);
	return ;
}

void	call_cmd(t_main *main, t_token *token)
{
	char	**new_env;

	if (!our_builtins(token->cmd))
	{
		new_env = linked_to_env(main->envs);
		exec_non_builtin_cmd(token, new_env);
		free_splits(new_env);
	}
	else
		check_builtins(main, token);
}
