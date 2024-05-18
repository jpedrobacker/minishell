/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_func.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:09:39 by aprado            #+#    #+#             */
/*   Updated: 2024/05/18 10:41:47 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*int	pre_execute(t_token **head)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (ft_putstr_fd("Error.\n", 2), 0);

}*/

//criar funcao para trocar o espaco que esta dentro das "" '' por \t
void	create_node(char *s, t_token **head, char ***paths, char **envp)
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
	new->envs_lst = envs;
	new->flag_expand = is_there_var(s);
	new->env = get_env_name(s, new->flag_expand);
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

t_token	create_list(char *usr_input, char **envp)
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
		create_node(splited[i], &head, &paths, envp);
		replace_char(splited[i], '\v', ' ');
		i++;
	}
	fix_matrix(&head);
	//pre_execute(&head);
	print_list(&head);
	//to_free_token(&head);
	//free_splits(splited);
	//free_splits(paths);
	return (*head);
}
