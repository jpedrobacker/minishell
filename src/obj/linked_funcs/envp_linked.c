/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_linked.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 11:55:58 by jbergfel          #+#    #+#             */
/*   Updated: 2024/06/13 11:36:58 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_env_key(char *envp, char c)
{
	int		len;
	int		i;
	char	*result;

	len = 0;
	while (envp[len] != '\0' && envp[len] != c)
		len++;
	result = (char*)malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = envp[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	**refill_envp(t_main *main)
{
	while (main->envs)
}

void	link_envp(char *envp, t_varenv **head)
{
	t_varenv	*node;
	t_varenv	*aux;

	node = malloc(sizeof(t_varenv));
	if (!node)
		return ;
	node->key = get_env_key(envp, '=');
	node->var = ft_memchr(envp, '=', ft_strlen(envp));
	node->full_env = ft_strdup(envp);
	node->next = NULL;
	if (!(*head))
	{
		(*head) = node;
		return ;
	}
	aux = (*head);
	while (aux->next)
		aux = aux->next;
	aux->next = node;
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
		node->full_env = ft_strdup(envp[i]);
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
	return (head);
}
