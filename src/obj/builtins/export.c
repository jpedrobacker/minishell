/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:38:28 by jbergfel          #+#    #+#             */
/*   Updated: 2024/05/10 17:15:59 by jbergfel         ###   ########.fr       */
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

void	link_envp(char *envp, t_varenv **head)
{
	t_varenv	*node;
	t_varenv	*aux;

	node = malloc(sizeof(t_varenv));
	if (!node)
		return ;
	node->key = get_env_key(envp, '=');
	node->var = ft_memchr(envp, '=', ft_strlen(envp));
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

void	print_list2(t_varenv **head)
{
	t_varenv	*aux;

	aux = *head;
	while (aux)
	{
		ft_printf("key: %s\n", aux->key);
		ft_printf("var: %s\n", aux->var);
		aux = aux->next;
	}
}

t_varenv	*built_export(char **envp)
{
	int	i;
	t_varenv	*head;
//	t_varenv	*aux;

	i = -1;
	head = NULL;
	while (envp[++i])
		link_envp(envp[i], &head);
	print_list2(&head);
	to_free_varenv(&head);
	return (0);
}


