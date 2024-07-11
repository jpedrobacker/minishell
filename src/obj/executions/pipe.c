/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:11:49 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/11 09:47:01 by jbergfel         ###   ########.fr       */
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
				return (perror("pipe"), 0);
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
}
