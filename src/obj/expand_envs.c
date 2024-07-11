/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:45:21 by aprado            #+#    #+#             */
/*   Updated: 2024/07/11 16:54:57 by aprado           ###   ########.fr       */
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
		if (!ft_strcmp(aux->key, name))
			return (aux->var);
		aux = aux->next;
	}
	return ("");
}

void	verify_quote(char c, t_helper *a)
{
	if (c == '"' && (a->one_q % 2) == 0)
		a->two_q++;
	else if (c == '\'' && (a->two_q % 2) == 0)
		a->one_q++;
}

void	new_expand_envs(char ***matrix, t_varenv *envs)
{
	t_helper	a;

	a = (t_helper){0};
	a.i = -1;
	while ((*matrix)[++a.i])
	{
		verify_quote((*matrix)[a.i][0], &a);
		if ((*matrix)[a.i][0] == '<' && (*matrix)[a.i + 1][0] == '<')
			a.hd = 1;
		else if (is_there_var((*matrix)[a.i]))
		{
			if ((a.one_q % 2) == 0 && a.hd == 0)
			{
				a.t = get_value_test((*matrix)[a.i] + 1, envs);
				if (a.t)
				{
					free((*matrix)[a.i]);
					(*matrix)[a.i] = NULL;
					(*matrix)[a.i] = ft_strdup(a.t);
				}
			}
			if ((*matrix)[a.i + 1] && (*matrix)[a.i + 1][0] == ' ')
				a.hd = 0;
		}
	}
}
