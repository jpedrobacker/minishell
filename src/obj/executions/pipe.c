/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:11:49 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/18 20:13:03 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	make_pipe(t_token *token)
{
	int		fd[2];
	t_token *cmds;

	while(token)
	{
		cmds = token;

	}
}
