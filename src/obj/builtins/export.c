/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:38:28 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/11 14:52:08 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_export(char *var)
{
	int	i;

	i = -1;
	if (!ft_isalpha(var[0]))
		return (1);
	while (var[++i])
	{
		if (var[i] == '=')
			return (0);
	}
	return (1);
}

int	check_var_exist(t_varenv **env, char *input)
{
	t_varenv	*aux;
	char		*key;
	char		*var;

	aux = (*(env));
	key = get_env_key(input, '=');
	var = ft_memchr(input, '=', ft_strlen(input));
	while (aux != NULL)
	{
		if (ft_strncmp(key, aux->key, ft_strlen(key)) == 0)
		{
			aux->var = var;
			free(key);
			return (0);
		}
		aux = aux->next;
	}
	free(key);
	return (1);
}

int	built_export(t_main **main)
{
	extern int	g_status;
	t_varenv	*aux_env;
	t_token		*aux_token;
	int			arrs;
	int			i;

	aux_env = (*main)->envs;
	aux_token = (*main)->cmds;
	arrs = count_cmds(aux_token->arr);
	if (arrs == 1)
		while (aux_env != NULL)
		{
			ft_printf("declare -x ");
			ft_printf("%s=", aux_env->key);
			ft_printf("\"%s\"\n", aux_env->var);
			aux_env = aux_env->next;
		}
	i = 1;
	while (aux_token->arr[i])
	{
		if (check_export(aux_token->arr[i]) == 0)
		{
			if (check_var_exist(&aux_env, aux_token->arr[i]) == 0)
				break ;
			else
				link_envp(aux_token->arr[i], &aux_env);
		}
		else
			errors_mini(QUOTE, "export");
		i++;
	}
	return (g_status = 127);
}
