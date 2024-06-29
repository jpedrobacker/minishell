/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:11:49 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/29 16:01:39 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	create_pipe(t_token *node, int size)
{
	int	fd[2];
	int	last_pipe = -1;
	int	counter = 1;

	if (size == 1) // Não há motivo para ter pipe, pois só temos 1 node.
		return 1;
	while (node)
	{
		if (counter != 1)
		{
			node->fd_in = last_pipe;
		}
		else
		{
			node->fd_in = STDIN_FILENO; // O primeiro node lê do terminal (stdin)
		}
		if (counter < size)
		{
			if (pipe(fd) == -1)
			{
				perror("pipe");
				return 0;
			}
			node->fd_out = fd[WRITE_END];
			last_pipe = fd[READ_END];
		}
		else
		{
			node->fd_out = STDOUT_FILENO; // O último node escreve no terminal (stdout)
		}
		//printf("Node %d: fd_in: %d, fd_out: %d\n", counter, node->fd_in, node->fd_out);
		counter++;
		node = node->next;
	}
	return 1;
}

/*
static int	create_pipe(t_token *node, int size)
{
	int		fd[2];
	int		last_pipe;
	int		counter;
	//t_token	*aux;

	//aux = node;
	counter = 1;
	if (size == 1) // nao tem motivo pra ter pipe... pois so temos 1 node.
		return (1);
	last_pipe = 0;
	while (node)
	{
		if (counter != 1)
			last_pipe = fd[READ_END];
		//aux = node->next; // aux ta no segundo node
		if (counter < size && pipe(fd) == -1)
			return (0);
		node->fd_in = last_pipe; //fd[last_pipe];
		last_pipe = fd[READ_END];
		node->fd_out = fd[WRITE_END];
		if (count == size) //| QUANDO FOR O ÚLTIMO NODE.
			node->fd_out = 1;
		else if (counter == 1) //| QUANDO FOR O PRIMEIRO NODE.
			node->fd_in = 0;
		if (counter == 1)
		{
			node->fd_in = 0;
			node->fd_out = fd[WRITE_END];
			ft_printf("fd_in: %i | fd_out: %i\n", node->fd_in, node->fd_out);
		}
		else if (counter < size)
		{
			node->fd_in = fd[READ_END];
			node->fd_out = fd[WRITE_END];
			ft_printf("fd_in: %i | fd_out: %i\n", node->fd_in, node->fd_out);
		}
		else
		{
			node->fd_in = fd[READ_END];
			node->fd_out = 1;
			ft_printf("fd_in: %i | fd_out: %i\n", node->fd_in, node->fd_out);
		}
		counter++;
		node = node->next;

		if (counter == 1)
		{
			//close(fd[0])??
			node->pipe_in = fd[READ_END];
			node->pipe_out = fd[WRITE_END]; // o primeiro no le do terminal e escreve no pipe()
		}
		else
		{

		}
		counter++;
		node = node->next;
	}
	return (1);
}
*/

int	make_pipe(t_main *bag)
{
	t_token	*aux;
	int		size;

	aux = bag->cmds;
	size = 1;
	while (aux->next)
	{
		size++;
		aux = aux->next;
	}
	if (!create_pipe(bag->cmds, size))
		return (0);
	return (1);
	/*
	int		fd[2];
	t_token	*cmds;

	while(token)
	{
		cmds = token;
		//while (token && token->flag != P)
		//	token = token->next
		token = token->next; //temporario
		ft_printf("----------%s---------\n", token->cmd);
		ft_printf("----------%s---------\n", cmds->cmd);
		if (!token)
			return (0);
		if (pipe(fd) == -1)
			return (1);
		cmds->fd_out = fd[1];
		ft_printf("----------%s---------\n", cmds->cmd);
		token = token->next;
		ft_printf("----------%s---------\n", cmds->cmd);
		if (cmds != NULL)
		{
			ft_printf("TESTE1\n");
			cmds->fd_in = fd[0];
		}
		else
		{
			ft_printf("Teste2\n");
			close(fd[0]);
			close(fd[1]);
		}
	}
	return (0);
	*/
}

void	close_fds(t_token *token)
{
	while (token)
	{
		if (token->fd_in != STDIN_FILENO)
			close(token->fd_in);
		else if (token->fd_out != STDOUT_FILENO)
			close(token->fd_out);
		token = token->next;
	}
	return ;
}

void	redir_(t_token *token)
{
	if (token->fd_out != STDOUT_FILENO)
		dup2(STDOUT_FILENO, token->fd_out);
	if (token->fd_in != STDIN_FILENO)
		dup2(STDIN_FILENO, token->fd_in);
}

void	exec_cmds_pipe(t_token *token, char **envp)
{
	redir_(token);
	close_fds(token);
	ft_printf("ANTES DO EXEC! %s\n", token->cmd);
	if (execve(token->real_path, token->arr, envp) == -1)
	{
		ft_putstr_fd("Command not found\n", 2);
		exit(127);
	}
	ft_printf("DEPOIS DO EXEC! %s\n", token->cmd);
	return ;
}

void	call_cmds_pipe(t_token *token)
{
	t_token	*exec;
	t_token	*temp;
	t_token	*temp2;
	pid_t pid;

	exec = token;
	while (exec)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(1);
		}
		else if (pid == 0)
		{
			ft_printf("CMD: %s, FD_IN: %d, FD_OUT: %d\n", exec->cmd, exec->fd_in, exec->fd_out);
			if (exec->fd_in != STDIN_FILENO)
				dup2(exec->fd_in, 0);
			if (exec->fd_out != STDOUT_FILENO)
				dup2(exec->fd_out, 1);
			temp = token;
			while (temp)
			{
				if (temp->fd_in != STDIN_FILENO)
					close(temp->fd_in);
				if (temp->fd_out != STDOUT_FILENO)
					close(temp->fd_out);
				temp = temp->next;
			}
			execve(exec->real_path, exec->arr, exec->envs);
			perror("execve");
			exit(1);
		}
		exec = exec->next;
	}
	temp2 = token;
	while(temp2)
	{
		if (temp2->fd_in != STDIN_FILENO)
			close(temp2->fd_in);
		if (temp2->fd_out != STDOUT_FILENO)
			close(temp2->fd_out);
		temp2 = temp2->next;
	}
	exec = token;
	while (exec)
	{
		wait(NULL);
		exec = exec->next;
	}
}
