/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:38:28 by jbergfel          #+#    #+#             */
/*   Updated: 2024/05/09 16:10:46 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*char	**ft_envsplit(char *envp)
{

}*/

void	link_envp(char *envp, t_varenv **head)
{
	t_varenv	*node;
	t_varenv	*aux;

	node = malloc(sizeof(t_varenv));
	if (!node)
		return ;
	//ft_printf("%s\n", envp);
	node->key = envp;
	node->next = NULL;
	ft_printf("-----%s\n", node->key);
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

void	teste(t_varenv **head)
{
	t_varenv	*aux;
	int i = 1;
	aux = *head;
	while (aux)
	{
		ft_printf("env: :AAAAAAAAA%sAAA\n", aux->key);
		aux = aux->next;
	}
}

t_varenv	*built_export(char **envp)
{
	int	i;
	t_varenv	*head;
	t_varenv	*aux;

	i = 0;
	//while (envp[i])
	//{
	ft_printf("test: %d\n", i);
	link_envp(envp[i], &head);
	aux = head;
	//while (aux)
	//{
	ft_printf("-> %s\n", aux->key);
	//aux = aux->next;
	//}
	ft_printf("-> %s\n", aux->key);
	teste(&head);
	return (0);
}


