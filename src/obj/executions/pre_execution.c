/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:39:47 by aprado            #+#    #+#             */
/*   Updated: 2024/07/06 17:57:50 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	pre_execute(t_token *token)
{
	if (token->fd_in == -1 || token->fd_out == -1)
		return (0);
	else if (!our_builtins(token->cmd) && !token->real_path)
	{
		write(2, token->cmd, ft_strlen(token->cmd));
		ft_putstr_fd(": command not found\n", 2);
		return (0);
	}
	return (1);
}
