/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:38:43 by jbergfel          #+#    #+#             */
/*   Updated: 2024/05/22 19:38:28 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	built_unset(t_varenv **env, t_token **token)
{
	t_varenv	*temp;
	t_varenv	*prev;
	t_token		*aux_token;

	temp = (*(env));
	prev = NULL;
	aux_token = (*(token));
	if (temp != NULL && ft_strncmp(temp->key, aux_token->arr_cmd_input[1], ft_strlen(temp->key)) == 0)
	{
		*env = temp->next;
		free(temp);
		return ;
	}
	while (temp != NULL && ft_strncmp(temp->key, aux_token->arr_cmd_input[1], ft_strlen(temp->key)) != 0)
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
	{
		errors_mini(QUOTE, "unset");
		return ;
	}
	prev->next = temp->next;
	free(temp);
}
