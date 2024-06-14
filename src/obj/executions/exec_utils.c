/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 21:44:10 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/12 21:57:23 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	token_fds_close(t_token *head)
{
	while (head)
	{
		if (head->fd_in != STDIN_FILENO)
			close(head->fd_in);
		else if (head->fd_out != STDOUT_FILENO)
			close(head->fd_out);
		head = head->next;
	}
	return ;
}
