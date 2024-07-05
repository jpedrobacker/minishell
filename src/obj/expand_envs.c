/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:45:21 by aprado            #+#    #+#             */
/*   Updated: 2024/07/05 11:01:20 by jbergfel         ###   ########.fr       */
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
	t_helper	a;

	a.i = -1;
	a.one_q = 0;
	a.two_q = 0;
	while ((*matrix)[++a.i])
	{
		if ((*matrix)[a.i][0] == 34 && (a.one_q % 2) == 0)
			a.two_q++;
		else if ((*matrix)[a.i][0] == 39 && (a.two_q % 2) == 0)
			a.one_q++;
		else if (is_there_var((*matrix)[a.i]))
		{
			if ((a.one_q % 2) == 0)
			{
				a.t = get_value_test((*matrix)[a.i] + 1, envs);
				if (a.t)
				{
					free((*matrix)[a.i]);
					(*matrix)[a.i] = NULL;
					(*matrix)[a.i] = ft_strdup(a.t);
				}
			}
		}
	}
	/*
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
	*/
}
