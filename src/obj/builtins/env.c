/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:38:53 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/07 20:03:46 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_env(char *key, char *var)
{
	if ((!ft_isalpha(key[0]) && key[0] != '_') || !var)
		return (1);
	return (0);
}

int	built_env(t_main *main, t_token *token)
{
	t_varenv	*aux_env;

	aux_env = main->envs;
	if (count_cmds(token->args) == 1)
	{
		if (!aux_env)
			ft_putendl_fd("env error!", 2);
		while (aux_env)
		{
			if (check_env(aux_env->key, aux_env->var) == 0)
			{
				ft_putstr_fd(aux_env->key, token->fd_out);
				ft_putstr_fd("=", token->fd_out);
				ft_putendl_fd(aux_env->var, token->fd_out);
			}
			aux_env = aux_env->next;
		}
	}
	else
	{
		errors_mini(ARGS, "env");
		return (127);
	}
	return (0);
}

//return de erros da env

/*
	Não há permissão do arquivo $? = 126
	Não há dir $? = 127
*/
