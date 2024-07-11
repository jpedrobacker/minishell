/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:39:47 by aprado            #+#    #+#             */
/*   Updated: 2024/07/11 09:49:16 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	pre_execute(t_token *token)
{
	if (token->fd_in == -1 || token->fd_out == -1)
		return (0);
	else if (!our_builtins(token->cmd) && !token->real_path)
	{
		replace_char(token->cmd, '\t', '|');
		replace_char(token->cmd, '\v', ' ');
		replace_char(token->cmd, '\n', '<');
		replace_char(token->cmd, '\a', '>');
		write(2, token->cmd, ft_strlen(token->cmd));
		ft_putstr_fd(": command not found\n", 2);
		g_status = 127;
		return (0);
	}
	return (1);
}

int	test_exec(t_token *token)
{
	if (token->fd_in == -1 || token->fd_out == -1)
		return (0);
	else if (!our_builtins(token->cmd) && !token->real_path)
	{
		g_status = 127;
		return (0);
	}
	return (1);
}
