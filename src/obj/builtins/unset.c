/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:38:43 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/10 22:23:12 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void to_free_temp(t_varenv *temp)
{
	free(temp->key);
	free(temp->var);
	free(temp);
}

int real_unset(t_varenv **env, const char *key_to_free)
{
	t_varenv *prev = NULL;
	t_varenv *cur = *env;

	while (cur)
	{
		if (strcmp(cur->key, key_to_free) == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				*env = cur->next;
			to_free_temp(cur);
			return (0);
		}
		prev = cur;
		cur = cur->next;
	}
	return (0);
}

int built_unset(t_main *main, t_token *token)
{
	int i = 1;
	while (token->args[i])
	{
		if (ft_strchr(token->args[i], '?'))
		{
			i++;
			continue;
		}
		real_unset(&(main->envs), token->args[i++]);
	}
	return (0);
}
