/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:38:28 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/09 11:54:21 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_export(char *key)
{
	if (key)
	{
		if (!ft_isalpha(key[0]) && key[0] != '_')
			return (1);
	}
	return (0);
}

void	print_export(t_token *token, t_varenv *env)
{
	while (env != NULL)
	{
		if (check_export(env->key) == 0)
		{
			ft_putstr_fd("declare -x ", token->fd_out);
			ft_putstr_fd(env->key, token->fd_out);
			if (env->var != NULL)
			{
				ft_putstr_fd("=\"", token->fd_out);
				if (env->var)
					ft_putstr_fd(env->var, token->fd_out);
				ft_putendl_fd("\"", token->fd_out);
			}
			else
				ft_putchar_fd('\n', token->fd_out);
		}
		env = env->next;
	}
}


int	check_var_exist(t_varenv *env, char *input)
{
	t_varenv	*aux;
	char		*key;
	char		*new_var;

	aux = env;
	key = get_env_key(input, '=');
	if (find_char(input, '=') == 0)
		new_var = ft_strdup((char *)ft_memchr(input, '=', ft_strlen(input)));
	while (aux)
	{
		if (ft_strcmp(key, aux->key) == 0)
		{
			if (find_char(input, '=') == 0)
				free(aux->var);
			aux->var = new_var;
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
		print_export(aux_token, aux_env);
	else
	{
		i = 0;
		while (aux_token->arr[++i])
		{
			if (check_export(aux_token->arr[i]) == 0)
			{
				if (check_var_exist(aux_env, aux_token->arr[i]) == 0)
					continue ;
				else
					link_envp(aux_token->arr[i], aux_env);
			}
			else
			{
				errors_mini(QUOTE, "export");
				return (127);
			}
		}
	}
	return (0);
}
