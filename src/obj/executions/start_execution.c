/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:26:30 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/25 21:11:07 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*void	close_all(t_token *token)
{

	if (token->fd_in != STDIN_FILENO)
		close(token->fd_in);
	if (token->fd_out != STDOUT_FILENO)
		close(token->fd_out);
	return ;
}*/

int	execution(t_main *main)
{
	t_token	*token;

	token = main->cmds;
	make_pipe(token);
	while (token)
	{
		if (exec_redirects(token, main) != 1)
			return (0);
		/*if (1)
			call_cmds_pipe(token);*/
		if (!check_builtins(main))
			call_cmd(main);
		//close_all(token);
		token = token->next;
	}
	return (0);
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

void	start_execution(char *usr_input, t_main *main)
{
	(void) usr_input;
	main->new_input = rev_split(main->splited_input);
	tokenize(main);

	//testing redirecting FDs
	execution(main);
	wait_all(main->cmds);
	//free do token
}

/*
	A FAZER
	FUNÇÃO PARA PREPARAR OS BUILT INS COM OS NOVOS FDS
	FUNÇÃO PARA FECHAR OS BUILT INS PÓS FDS
	FUNÇÃO EXCLUSIVA PARA REDIRECT DOS BUILT INS
	EXIT STATUS DE TODOS OS BUILT INS
	MELHORAR E BOTAR PRA FUNCIONAR A FUNÇÃO DE FDS IN E OUT
*/
