/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_func.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:09:39 by aprado            #+#    #+#             */
/*   Updated: 2024/05/07 14:59:09 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//criar funcao para trocar o espaco que esta dentro das "" '' por \t
void	create_node(char *s, t_token **head, char ***paths)
{
	t_token	*new;
	t_token	*current;

	new = malloc(sizeof(t_token));
	if(!new)
		return (ft_putstr_fd("Error\n", 2));
	new->cmd_input = s;
	new->arr_cmd_input = ft_split(s, ' ');
	new->cmd_name = divide_command_input(s);
	new->real_path = get_real_path(paths, new->cmd_name);
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

void	create_list(char *usr_input, char **envp)
{
	t_token	*head;
	char	**splited;
	char	**paths;
	char	*env_path;
	int		i;

	i = 0;
	head = NULL;
	splited = ft_split(usr_input, '|');
	env_path = find_env_path(envp);
	paths = ft_split((env_path + 5), ':');
	while (splited[i])
	{
		//ft_printf("OPAAA\n");
		replace_char(splited[i], '\t', '|');
		create_node(splited[i], &head, &paths);
		replace_char(splited[i], '\v', ' ');
		i++;
	}
	fix_matrix(&head);
	print_list(&head);
}
