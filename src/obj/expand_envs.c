/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:45:21 by aprado            #+#    #+#             */
/*   Updated: 2024/05/27 14:20:34 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_varenv	*get_value(char *name, t_varenv *envs)
{
	t_varenv	*aux;

	aux = envs;
	while (aux)
	{
		if (!ft_strncmp(aux->key, name, ft_strlen(name)))
				return (aux);
		aux = aux->next;
	}
	return (NULL);
}

void	expand_envs(char ***matrix, t_varenv *envs)
{
	t_varenv	*aux;
	char		*env;
	char		*temp;
	char		**s;
	int			i;

	i = 0;
	env = NULL;
	s = *matrix;
	while (s[i])
	{
		env = get_env_name(s[i], 1);
		//ft_printf("env name :%s:\n", env);
		if (env)
		{
			aux = get_value(env, envs);
			if (aux)
			{
				ft_printf("ENV VALUE :%s:\n", aux->var);
				temp = s[i];
				s[i] = ft_strdup(aux->var);
				free(temp);
			}
			//ft_printf("DEI FREE no %s\n", env);
			//ft_printf("%x\n", temp);
			//ft_printf("%x\n", env);
			//free(env); //dando double free??
			//ft_printf("AFTER FREE no %s\n", env);
			//env = NULL;
		}
		i++;
	}
}
