/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:29:24 by jbergfel          #+#    #+#             */
/*   Updated: 2024/04/29 15:58:33 by jbergfel         ###   ########.fr       */
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

char	*find_env_path(char **envp)
{
	char	*env_path;
	int		i;

	i = 0;
	env_path = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			env_path = envp[i];
			break ;
		}
		i++;
	}
	return (env_path);
}

void	create_list(char *usr_input, char **envp)
{
	t_token	*head;
	char	**splited;
	char	**paths;
	char	*env_path;
	int		i;
	(void) envp;
	i = 0;
	head = NULL;
	splited = ft_split(usr_input, ' ');
	env_path = getenv("PATH");
	paths = ft_split((env_path + 5), ':');
	ft_printf("env path: %s\n", env_path);
	ft_printf("first path: %s\n", paths[0]);
	while (splited[i])
	{
		create_node(splited[i], &head);
		i++;
	}
	print_list(&head);
}

int	main(int ac, char **av, char **envp)
{
	char	*usr_input;
	(void) ac;
	(void) av;
	while (1)
	{
		usr_input = readline("minishell: ");
		add_history(usr_input);
		create_list(usr_input, envp);
		free(usr_input);
	}
	return (1);
}
