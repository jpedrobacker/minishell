/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:29:24 by jbergfel          #+#    #+#             */
/*   Updated: 2024/04/27 17:22:07 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_list(t_token **head)
{
	t_token	*aux;

	aux = *head;
	while (aux)
	{
		ft_printf("-> %s\n", aux->command);
		aux = aux->next;
	}
}

void	create_node(char *s, t_token **head)
{
	t_token	*new;
	t_token	*current;

	new = malloc(sizeof(t_token));
	if(!new)
		return (ft_putstr_fd("Error\n", 2));
	new->command = s;
	new->next = NULL;
	if (!(*head))
	{
		(*head) = new;
		return ;
	}
	current = (*head);
	while (current->next)
		current = current->next;
	current->next = new;
}

void	create_list(int ac, char **av, char **envp)
{
	t_token	*head;
	char	**splited;
	int		i;

	(void)ac;
	(void)envp;
	i = 0;
	head = NULL;
	splited = ft_split(av[1], '|');
	while (splited[i])
	{
		create_node(splited[i], &head);
		i++;
	}
	print_list(&head);
}

int	main(int ac, char **av, char **envp)
{
	if (ac != 2)
		return (ft_putstr_fd("Missing parameters\n", 2), 0);
	create_list(ac, av, envp);
	return (1);
}

/*
int main (void)
{
	ft_printf("TESTE1\n");
	test_print("TESTE2");
	return (0);
}
*/
