/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:38:28 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/04 13:42:13 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_export(char *var)
{
	if (!ft_isalpha(var[0]))
		return (1);
	return (0);
}

int	check_var_exist(t_varenv *env, char *input)
{
	t_varenv	*aux;
	char		*key;
	char		*var;

	aux = env;
	key = get_env_key(input, '=');
	var = ft_memchr(input, '=', ft_strlen(input));
	while (aux != NULL)
	{
		if (ft_strcmp(key, aux->key) == 0)
		{
			aux->var = var;
			free(aux->full_env);
			aux->full_env = ft_strdup(input);
			free(key);
			return (0);
		}
		aux = aux->next;
	}
	free(key);
	return (1);
}

int	built_export(t_varenv *env, t_token *token)
{
	t_varenv	*aux_env;
	t_token		*aux_token;
	int			arrs;
	int			i;

	aux_env = env;
	aux_token = token;
	arrs = count_cmds(aux_token->arr);
	if (arrs == 1)
	{
		while (aux_env != NULL)
		{
			if (!ft_strcmp("?", aux_env->key))
			{
				ft_putstr_fd("declare -x ", aux_token->fd_out);
				ft_putstr_fd(aux_env->key, aux_token->fd_out);
				ft_putstr_fd("=\"", aux_token->fd_out);
				ft_putstr_fd(aux_env->var, aux_token->fd_out);
				ft_putendl_fd("\"", aux_token->fd_out);
			}
			aux_env = aux_env->next;
		}
		return (0);
	}
	else
	{
		i = 1;
		while (aux_token->arr[i])
		{
			if (check_export(aux_token->arr[i]) == 0)
			{
				if (check_var_exist(aux_env, aux_token->arr[i]) == 0)
					break ;
				else
					link_envp(aux_token->arr[i], aux_env);
			}
			else
			{
				errors_mini(QUOTE, "export");
				return (127);
			}
			i++;
		}
	}
	return (0);
}
