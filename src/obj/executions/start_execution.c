/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:26:30 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/27 17:59:37 by aprado           ###   ########.fr       */
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

void	begin_exec(t_main *bag)
{
	t_token	*aux;
	pid_t		pid;
	int			fd[2];
	int			node;

	aux = bag->cmds;
	node = 0;
	while (aux)
	{
		if (!aux->next && node == 0)
		{
			pid = fork();
			if (pid < 0)
				break ; // ERROR, preciso dar free em tudo
			if (pid == 0)
			{
				if (aux->fd_in != 0)
					if (dup2(aux->fd_in, READ_END) == -1)
						ft_putstr_fd("TESTE\n", 2);
				if (aux->fd_out != 0)
					if (dup2(aux->fd_out, WRITE_END) == -1)
						ft_putstr_fd("TESTE\n", 2);
				//if (for nossos builtins) = manda pra eles
				//else = manda pro execve
				execve(aux->real_path, aux->args, NULL);
			}
			else
				waitpid(pid, NULL, 0);
		}
		else
		{
			if (pipe(fd) == -1)
				break ; // ERROR, PRECISO DAR FREE EM TUDO
			if ((pid = fork()) < 0)
				break ; // ERROR, PRECISO DAR FREE EM TUDO
			if (pid == 0) //CHILD PROCESS
			{
				if (aux->fd_in != 0)
				{
					if (dup2(aux->fd_in, READ_END) == -1)
						ft_putstr_fd("TESTE\n", 2);
				}
				else if (node != 0)
					if (dup2(fd[0], READ_END) == -1)
						ft_putstr_fd("Error\n", 2);
				if (aux->fd_out != 0)
				{
					if (dup2(aux->fd_out, WRITE_END) == -1)
						ft_putstr_fd("TESTE\n", 2);
				}
				else if (node != 0)
					if (dup2(fd[1], WRITE_END) == -1)
						ft_putstr_fd("TESTE\n", 2);
				//if (for nossos builtins) = manda pra eles
				//else = manda pro execve
				execve(aux->real_path, aux->args, NULL);
			}
			else
			{
				waitpid(pid, NULL, 0);
				//close(fd[1]);
			}
			//CLOSE FDS NECESSARIOS
		}
		node++;
		aux = aux->next;
	}
}

void	start_execution(char *usr_input, t_main *main)
{
	(void) usr_input;
	main->new_input = rev_split(main->splited_input);
	tokenize(main); // Todas as estruturas estao organizadas aqui...
	ordering_fds(main); // Agora, faremos a mudanca dos fds...
	begin_exec(main); // Agora, faremos o inicio da execucao...
	
	//testing redirecting FDs
	//test_execution(main);

	//execution(main);
	//waitpid dos comandos
	//free do token
}
