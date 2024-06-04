/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:38:53 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/02 15:48:49 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	built_env(t_token **token, t_varenv **env)
{
	t_token	*aux_token;
	t_varenv *aux_env;
	char	**args;

	aux_token = (*(token));
	aux_env = (*(env));
	args = aux_token->arr_cmd_input;
	if (!aux_token->arr_cmd_input ||count_cmds(args) < 2)
	{
		if (!aux_env)
			ft_printf("MERDA DE PROJETO\n");
		while (aux_env)
		{
			ft_printf("%s=", aux_env->key);
			ft_printf("%s\n", aux_env->var);
			aux_env = aux_env->next;
		}
		ft_printf("AAAAAAAAAA\n");
	}
	else
		errors_mini(ARGS, "env");
}
