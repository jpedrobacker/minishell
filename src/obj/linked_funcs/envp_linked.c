/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_linked.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 11:55:58 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/09 15:48:44 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	link_envp(char *envp, t_varenv *head)
{
	t_varenv	*node;
	t_varenv	*aux;

	node = malloc(sizeof(t_varenv));
	if (!node)
		return ;
	node->key = get_env_key(envp, '=');
	if (find_char(envp, '=') == 0)
		node->var = ft_strdup(ft_strchr(envp, '='));
	else
		node->var = NULL;
	node->next = NULL;
	if (!head)
	{
		head = node;
		return ;
	}
	aux = head;
	while (aux->next)
		aux = aux->next;
	aux->next = node;
}

void	add_gstatus_to_env(t_varenv *envs)
{
	char		*str_gstatus;

	str_gstatus = ft_strdup("?=0");
	link_envp(str_gstatus, envs);
	free(str_gstatus);
}

t_varenv	*make_envp_list(char **envp)
{
	int			i;
	t_varenv	*node;
	t_varenv	*head;
	t_varenv	*temp;

	i = 0;
	head = NULL;
	while (envp[i] != NULL)
	{
		node = malloc(sizeof(t_varenv));
		if (!node)
			return (NULL);
		node->key = get_env_key(envp[i], '=');
		if (find_char(envp[i], '=') == 0)
			node->var = ft_strdup(ft_strchr(envp[i], '='));
		node->next = NULL;
		if (head == NULL)
		{
			head = node;
			node->head = node;
		}
		else
		{
			temp = head;
			while (temp->next)
				temp = temp->next;
			temp->next = node;
			node->head = head;
		}
		i++;
	}
	add_gstatus_to_env(head);
	return (head);
}
