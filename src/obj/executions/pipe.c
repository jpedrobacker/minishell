/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:11:49 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/10 14:19:09 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	create_pipe(t_token *node, int size)
{
	int	fd[2];
	int	last_pipe;
	int	counter;

	last_pipe = -1;
	counter = 1;
	if (size == 1)
		return (1);
	while (node)
	{
		if (counter != 1)
			node->fd_in = last_pipe;
		else
			node->fd_in = STDIN_FILENO;
		if (counter < size)
		{
			if (pipe(fd) == -1)
			{
				perror("pipe");
				return (0);
			}
			node->fd_out = fd[WRITE_END];
			last_pipe = fd[READ_END];
		}
		else
			node->fd_out = STDOUT_FILENO;
		counter++;
		node = node->next;
	}
	return (1);
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
	size = 0;
	while (aux)
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
