/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:38:43 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/07 13:59:57 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	built_unset(t_main **main)
{
	t_varenv	*temp;
	t_varenv	*prev;
	t_token		*aux_token;
	int			i;

	temp = (*main)->envs;
	prev = NULL;
	aux_token = (*main)->cmds;
	i = 1;
	while (aux_token->arr[i])
	{
		while (temp != NULL)
		{
			if (temp != NULL && ft_strcmp(temp->key, aux_token->arr[i]) == 0)
				free(temp);
			prev = temp;
			temp = temp->next;
		}
		i++;
	}
	if (temp == NULL)
	{
		errors_mini(QUOTE, "unset");
		return ;
	}
	prev->next = temp->next;
	free(temp);
}
