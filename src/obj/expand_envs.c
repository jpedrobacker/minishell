/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:45:21 by aprado            #+#    #+#             */
/*   Updated: 2024/06/22 17:34:24 by aprado           ###   ########.fr       */
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

static char	*get_value_test(char *name, t_varenv *envs)
{
	t_varenv	*aux;

	aux = envs;
	while (aux)
	{
		if (!ft_strncmp(aux->key, name, ft_strlen(name)))
			return (aux->var);
		aux = aux->next;
	}
	return (NULL);
}

void	new_expand_envs(char ***matrix, t_varenv *envs)
{
	char		*temp;
	char		**s;
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
				temp = get_value_test(s[i] + 1, envs);
				if (temp)
				{
					free(s[i]);
					s[i] = NULL;
					s[i] = ft_strdup(temp);
				}
			}
		}
		i++;
	}
}
