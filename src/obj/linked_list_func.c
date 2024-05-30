/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_func.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:09:39 by aprado            #+#    #+#             */
/*   Updated: 2024/05/30 18:27:35 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	prepare_nodes(t_token **head)
{
	fix_matrix(head);
	print_list(head);
}

void	create_node(char *s, t_token **head, char ***paths, t_varenv *envs)
{
	t_token	*new;
	t_token	*current;

	new = malloc(sizeof(t_token));
	if (!new)
		return (ft_putstr_fd("Error\n", 2));
	new->cmd_input = s;
	new->arr_cmd_input = ft_split(s, ' ');
	new->cmd_name = divide_command_input(s);
	new->real_path = get_real_path(paths, new->cmd_name);
	new->envs_lst = envs;
	new->flag_expand = is_there_var(s);
	new->env = get_env_name(s, new->flag_expand, ft_strlen(s));
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

t_token	*create_list(char *usr_input, t_varenv *envs)
{
	t_token	*head;
	char	**splited;
	char	**paths;
	char	*env_path;
	int		i;

	i = 0;
	head = NULL;
	splited = ft_split(usr_input, '|');
	env_path = find_env_path(envs);
	paths = ft_split(env_path, ':');
	while (splited[i])
	{
		replace_char(splited[i], '\t', '|');
		create_node(splited[i], &head, &paths, envs);
		replace_char(splited[i], '\v', ' ');
		i++;
	}
	fix_matrix(&head);
	//get_expanded_env(&head);
	print_list(&head);
	//to_free_token(&head);
	free_splits(splited);
	free_splits(paths);
	return (head);
}
