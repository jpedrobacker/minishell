/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:26:30 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/13 16:27:28 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	call_cmd(t_main *main)
{
	extern int	g_status;
	t_token	*token;
	int status;

	token = main->cmds->head;
	token->pid = fork();
	token->envs = update_envp(main->env);
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

int	execution(t_main *main)
{
	t_token	*token;
	int		have_pipe;
	int		have_redir;

	token = main->token;
	//função para prepara o pipe
	have_pipe = 0;
	while (token)
	{
		if (!check_builtins(main))
			call_cmd(main);
		else
			return (-1);
		//função para fechar fds abrangendo o pipe
		//função para chamar o proximo pipe
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
