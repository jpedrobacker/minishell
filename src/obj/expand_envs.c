/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:45:21 by aprado            #+#    #+#             */
/*   Updated: 2024/06/01 10:49:36 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"


//Podemos fazer essa func retornar o ponteiro pro valor da env.
//dessa forma, nos poupa linha na new_expand_env();
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

void	new_expand_envs(char ***matrix, t_varenv *envs)
{
	t_varenv	*aux;
//	char		*temp;
	char		**s;
//	char		*env;
	int			i;
	int			one_q;
	int			two_q;

	i = 0;
	one_q = 0;
	two_q = 0;
	s = *matrix;
	while (s[i])
	{
		if (s[i][0] == 34 && (one_q % 2) == 0)
			two_q++;
		else if (s[i][0] == 39 && (two_q % 2) == 0)
			one_q++;
		else if (is_there_var(s[i]))
		{
			if ((one_q % 2) == 0)
			{
				//env = get_env_name(s[i], 1, ft_strlen(s[i]));
				//aux = get_value(env, envs);
				aux = get_value(s[i] + 1, envs);
				free(s[i]);
				s[i] = NULL;
				//temp = matrix[i];
				s[i] = ft_strdup(aux->var);
				//free(temp);
				//free(env);
			}
		}
		i++;
	}
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
		env = get_env_name(s[i], 1, ft_strlen(s[i]));
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
