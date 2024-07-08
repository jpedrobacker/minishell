/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_linked.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 11:55:58 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/07 20:16:57 by jbergfel         ###   ########.fr       */
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
	node->var = ft_memchr(envp, '=', ft_strlen(envp));
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
	char		*g_status_itoa;

	g_status_itoa = ft_itoa(g_status);
	str_gstatus = ft_strjoin("?=" , g_status_itoa);
	link_envp(str_gstatus, envs);
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
		node->var = ft_memchr(envp[i], '=', ft_strlen(envp[i]));
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
