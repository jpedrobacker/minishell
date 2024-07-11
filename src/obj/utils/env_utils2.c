/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:39:40 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/11 10:40:54 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	env_lst_size(t_varenv *env)
{
	int			i;
	t_varenv	*temp;

	temp = env;
	i = 0;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

char	*find_var_key(t_varenv *env, char *key_to_find)
{
	t_varenv	*aux;

	aux = env;
	while (aux != NULL)
	{
		if (ft_strcmp(aux->key, key_to_find) == 0)
			return (aux->var);
		aux = aux->next;
	}
	return ("");
}
