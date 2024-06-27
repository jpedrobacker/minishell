/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:26:30 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/27 10:47:18 by aprado           ###   ########.fr       */
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
		bag->cmds->fd_in = open(bag->cmds->arr[1], O_RDONLY);
		bag->cmds->fd_out = open(bag->cmds->arr[4], O_CREAT | O_RDWR | O_TRUNC, 00700);
		if (dup2(bag->cmds->fd_in, 0) == -1)
			ft_putstr_fd("TESTE\n", 2);
		if (dup2(bag->cmds->fd_out, 1) == -1)
			ft_putstr_fd("TESTE\n", 2);
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
	tokenize(main); // Todas as estruturas estao organizadas aqui...
	ordering_fds(main); // Agora, fazemos a mudanca dos fds...
	
	//testing redirecting FDs
	//test_execution(main);

	//execution(main);
	//waitpid dos comandos
	//free do token
}
