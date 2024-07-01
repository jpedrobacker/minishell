/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:26:30 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/01 18:09:12 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	close_all(t_token *token)
{

	if (token->fd_in != STDIN_FILENO)
		close(token->fd_in);
	if (token->fd_out != STDOUT_FILENO)
		close(token->fd_out);
	return ;
}

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
	if (!make_pipe(main)) // ESTA FUNCIONANDO
		ft_putstr_fd("Error\n", 2);
	if (!ordering_fds(main)) // ja abre os pipes, se tiver, e faz os redirecionamentos, se tiver.
		ft_putstr_fd("Error\n", 2);
	//-------------------------------------------------------------------
	//------- ATE AQUI ESTA FUNCIONANDO CORRETAMENTE, EU ACHO -----------
	//-------------------------------------------------------------------
	//---------------- DAQUI PRA BAIXO, AINDA NAO -----------------------
	//-------------------------------------------------------------------
	//prepare_pipes(main->cmds);
	//
	//------------------------------------------
	//--------- Passando a norma----------------
	//-----------------------------------------
	


	//call_cmds_pipe(main);


	//make_pipe(token);
	//testing redirecting FDs
	//execution(main);
	//wait_all(main->cmds);
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

//-------------------------------------------------------------------
//---------------- feat_execution ----------------------------------
/*
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
*/
