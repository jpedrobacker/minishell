/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:38:43 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/10 13:57:12 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		real_unset(t_varenv **env, char **cmds)
{
	t_varenv	*temp;
	t_varenv	*prev;
	t_varenv	*cur;
	int			i;

	i = 1;
	while (cmds[i])
	{
		if (ft_strcmp((*env)->key, cmds[i]) == 0)
		{
			temp = *env;
			*env = (*env)->next;
			free(temp->key);
			free(temp);
		}
		prev = *env;
		cur = prev->next;
		while (cur)
		{
			if (ft_strcmp(cur->key, cmds[i]) == 0)
			{
				prev->next = cur->next;
				free(cur->key);
				free(cur);
			}
			prev = cur;
			cur = cur->next;
		}
		i++;
	}
	return (0);
}

void	built_unset(t_main *main)
{
	real_unset(&main->envs, main->cmds->arr);
}
