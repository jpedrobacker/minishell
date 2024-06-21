/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:11:49 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/20 13:53:34 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	make_pipe(t_token *token)
{
	int		fd[2];
	t_token	*cmds;

	while(token)
	{
		cmds = token;
		/*while (token && token->flag != P)
			token = token->next*/
		token = token->next; //temporario
		if (!token)
			return (0);
		if (pipe(fd) == -1)
			return (1);
		cmds->fd_out = fd[1];
		token = token->next;
		cmds = token;
		if (cmds)
			cmds->fd_in = fd[0];
		else
		{
			close(fd[0]);
			close(fd[1]);
		}
	}
	return (0);
}
