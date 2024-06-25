/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:26:30 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/25 10:57:56 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	execution(t_main *main)
{
//	t_token	*token;
	//int		have_pipe;
	///int		have_redir;

//	token = main->cmds;
	//função para prepara o pipe
	//have_pipe = 0;

	if (!check_builtins(main))
		call_cmd(main);
	else
		return (-1);
		//função para fechar fds abrangendo o pipe
		//função para chamar o proximo pipe
	return (0);
}

/*
void	test_execution(t_main *bag)
{
	(void)bag;
	pid_t	pid;
	char	*s[] = {"cat", NULL};

	pid = fork();
	if (pid < 0)
		ft_putstr_fd("fork Error\n", 2);
	if (pid == 0)
	{
		ft_printf("processo forkado\n");
		execve("/usr/bin/cat", s, NULL);
	}
	else
		waitpid(pid, NULL, 0);
	close(bag->cmds->fd_in);
	close(bag->cmds->fd_out);
}
*/

void	start_execution(char *usr_input, t_main *main)
{
	(void) usr_input;
	main->new_input = rev_split(main->splited_input);
	tokenize(main);


	//testing redirecting FDs
	//test_execution(main);

	//execution(main);
		//waitpid dos comandos
	//free do token
}
