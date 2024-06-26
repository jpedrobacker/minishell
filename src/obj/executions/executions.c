/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:00:52 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/25 21:13:32 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exec_non_builtin_cmd(t_token *token, char **env)
{
	if (token->fd_in != STDIN_FILENO)
		dup2(token->fd_in, STDIN_FILENO);
	if (token->fd_out != STDOUT_FILENO)
		dup2(token->fd_out, STDOUT_FILENO);
	token_fds_close(token->head);
	if (execve(token->real_path, token->args, env) == -1)
	{
		if (errno == ENOENT)
			ft_printf("Commoutand not found!\n");
		exit(127);
	}
	else
		exit(EXIT_SUCCESS);
}

int	call_cmd(t_main *main)
{
	extern int	g_status;
	t_token	*token;
	int status;

	token = main->cmds;
	token->pid = fork();
	token->envs = update_envp(main->envs);
	if (token->pid < 0)
	{
		perror("Fork failed!\n");
		exit(EXIT_FAILURE);
	}
	else if (token->pid == 0)
		exec_non_builtin_cmd(token, token->envs);
	else
		waitpid(token->pid, &status, 0);
	g_status = WEXITSTATUS(status);
	return (1);
}
