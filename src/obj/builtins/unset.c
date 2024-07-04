/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:38:43 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/04 12:01:01 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		real_unset(t_varenv *env, char **cmds)
{
	t_varenv	*temp;
	t_varenv	*prev;
	t_varenv	*cur;
	int			i;

	i = 1;
	while (cmds[i])
	{
		if (ft_strcmp(env->key, cmds[i]) == 0)
		{
			temp = env;
			env = env->next;
			free(temp->key);
			free(temp->full_env);
			free(temp);
		}
		prev = env;
		cur = prev->next;
		while (cur)
		{
			if (ft_strcmp(cur->key, cmds[i]) == 0)
			{
				prev->next = cur->next;
				free(cur->key);
				free(cur->full_env);
			}
			prev = cur;
			cur = cur->next;
		}
		i++;
	}
	return (1);
}

int	built_unset(t_main *main, t_token *token)
{
	return (real_unset(main->envs, token->args));
}
