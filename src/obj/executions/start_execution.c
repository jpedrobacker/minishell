/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:26:30 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/18 20:12:04 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	execution(t_main *main)
{
	t_token	*token;

	token = main->cmds;
	make_pipe(token);
	while (token)
	{
		if (1)
			exec_pipe(token)
		else if (!check_builtins(main))
			call_cmd(main);
		//função para fechar fds abrangendo o pipe
		//função para chamar o proximo pipe
	}
	return (0);
}

void	start_execution(char *usr_input, t_main *main)
{
	(void) usr_input;
	main->new_input = rev_split(main->splited_input);
	tokenize(main);
	execution(main);
	//waitpid dos comandos
	//free do token
}
