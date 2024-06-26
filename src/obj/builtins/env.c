/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:38:53 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/25 15:23:52 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	built_env(t_main **main)
{
	extern int	g_status;
	t_varenv	*aux_env;
	t_token		*aux_token;
	char		**args;

	aux_token = (*main)->cmds;
	aux_env = (*main)->envs;
	args = aux_token->arr;
	if (count_cmds(args) < 2)
	{
		if (!aux_env)
			ft_putendl_fd("env error!", 2);
		while (aux_env)
		{
			ft_putendl_fd(aux_env->full_env, aux_token->fd_out);
			aux_env = aux_env->next;
		}
	}
	else
	{
		errors_mini(ARGS, "env");
		return (g_status = 127);
	}
	return (g_status = 1);
}

//return de erros da env

/*
	Não há permissão do arquivo $? = 126
	Não há dir $0 = 127
*/
