/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:00:52 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/24 14:30:14 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_builtins(t_main *main)
{
	int	status;

	status = 0;
	if (ft_strcmp("cd", main->cmds->arr[0]) == 0)
		status = built_cd(&main);
	if (ft_strcmp("echo", main->cmds->arr[0]) == 0)
		status = built_echo(&main, echo_flag(main->cmds->arr));
	if (ft_strcmp("env", main->cmds->arr[0]) == 0)
		status = built_env(&main);
	if (ft_strcmp("exit", main->cmds->arr[0]) == 0)
		built_exit(main);
	if (ft_strcmp("pwd", main->cmds->arr[0]) == 0)
		status = built_pwd();
	if (ft_strcmp("export", main->cmds->arr[0]) == 0)
		status = built_export(&main);
	if (ft_strcmp("unset", main->cmds->arr[0]) == 0)
		status = built_unset(main);
	if (ft_strcmp("clear", main->cmds->arr[0]) == 0)
		status = built_clear();
	return (status);
}

void	exec_non_builtin_cmd(t_token *token, char **env)
{
	char	**cmds;
//	char	*test[] = {"cat", NULL};
//	char	*pathtest = "/usr/bin/cat"

	copy_char_pointer(&cmds, token->arr);
	/*
	if (token->fd_out != STDOUT_FILENO)
		dup2(token->fd_out, STDOUT_FILENO);
	if (token->fd_in != STDIN_FILENO)
		dup2(token->fd_in, STDIN_FILENO);
	token_fds_close(token->head);
	ft_printf("TESTE\n");
	*/
	if (execve(token->real_path, cmds, env) == -1)
	{
		if (errno == ENOENT)
			ft_printf("Commoutand not found!\n");
		free_splits(cmds);
		exit(127);
	}
	else
	{
		free_splits(cmds);
		exit(EXIT_SUCCESS);
	}
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
