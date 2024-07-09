/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:38:43 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/09 11:42:03 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	to_free_temp(t_varenv *temp)
{
	free(temp->key);
	free(temp->var);
	free(temp);
	return ;
}

int	real_unset(t_varenv *env, char **cmds)
{
	t_varenv	*temp;
	t_varenv	*prev;
	t_varenv	*cur;
	int			i;

	i = 0;
	while (cmds[++i])
	{
		if (ft_strcmp(env->key, cmds[i]) == 0)
		{
			temp = env;
			env = env->next;
			to_free_temp(temp);
		}
		prev = env;
		cur = prev->next;
		while (cur)
		{
			if (ft_strcmp(cur->key, cmds[i]) == 0)
			{
				prev->next = cur->next;
				free(cur->key);
				if (cur->var != NULL)
					free(cur->var);
			}
			prev = cur;
			cur = cur->next;
		}
	}
	return (0);
}

int	built_unset(t_main *main, t_token *token)
{
	return (real_unset(main->envs, token->args));
}
