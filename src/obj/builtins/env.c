/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:38:53 by jbergfel          #+#    #+#             */
/*   Updated: 2024/05/21 13:22:47 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	built_env(t_varenv **envp, t_token **token)
{
	t_varenv	*aux_env;
	t_token		*aux_token;
	char		**args;

	aux_token = (*(token));
	aux_env = (*(envp));
	args = aux_token->arr_cmd_input;
	if (count_cmds(args) < 2)
	{
		while (aux_env)
		{
			ft_printf("%s=", aux_env->key);
			ft_printf("%s\n", aux_env->var);
			aux_env = aux_env->next;
		}
	}
	else
		errors_mini(ARGS, "env");
}
