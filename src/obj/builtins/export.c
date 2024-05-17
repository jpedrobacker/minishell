/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:38:28 by jbergfel          #+#    #+#             */
/*   Updated: 2024/05/16 21:00:53 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_export(char *var)
{
	int	i;

	i = -1;
	while(var[++i])
	{
		if (var[i] == '=')
			return (0);
	}
	return (1);
}

void	built_export(t_varenv **env, t_token **token)
{
	t_varenv	*aux_env;
	t_token		*aux_token;
	int			arrs;
	int			i;

	aux_env = (*(env));
	aux_token = (*(token));
	arrs = count_cmds(token);
	if (arrs == 1)
	{
		while(aux_env != NULL)
		{
			ft_printf("declare -x ");
			ft_printf("%s=", aux_env->key);
			ft_printf("\"%s\"\n", aux_env->var);
			aux_env = aux_env->next;
		}
	}
	i = 1;
	while (aux_token->arr_cmd_input[i])
	{
		if (check_export(aux_token->arr_cmd_input[i]) == 0)
			link_envp(aux_token->arr_cmd_input[i], &aux_env);
		i++;
	}
}
