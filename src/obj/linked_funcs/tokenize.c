/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:13:15 by aprado            #+#    #+#             */
/*   Updated: 2024/06/14 19:48:59 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#include "../inc/minishell.h"

static void	init_bag(t_main *bag)
{
	bag->cmds = NULL;
	bag->splited_pipe = ft_split(bag->new_input, '|');
	bag->envs_path = find_env_path(bag->envs);
	bag->paths = ft_split(bag->envs_path, ':');
	replace_char(bag->new_input, '\t', '|');
	replace_char(bag->new_input, '\v', ' ');
}

void	create_token(char *s, t_token **head, t_main *bag)
{
	t_token		*new;
	t_token		*current;

	new = malloc(sizeof(t_token));
	if (!new)
		return (ft_putstr_fd("ERROR\n", 2));
	new->arr = ft_split(s, ' ');
	new->token = s;
	new->real_path = get_real_path(&bag->paths, new->arr[0]);
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

void	print_node(t_main *bag)
{
	t_token		*aux;
	int		i;
	int		x;

	aux = bag->cmds;
	i = 1;
	x = 0;
	while (aux)
	{
		x = 0;
		ft_printf("----- NODE: %i -----\n", i);
		ft_printf("token :%s: \n", aux->token);
		while (aux->arr[x])

		{
			ft_printf("matrix :%s: \n", aux->arr[x]);
			x++;
		}
		ft_printf("path :%s: \n", aux->real_path);
		aux = aux->next;
		i++;
	}
}

void	tokenize(t_main *bag)
{
	int	i;

	i = 0;
	init_bag(bag);

	while (bag->splited_pipe[i])
	{
		create_token(bag->splited_pipe[i], &bag->cmds, bag);
		replace_char(bag->splited_pipe[i], '\t', '|');
		replace_char(bag->splited_pipe[i], '\v', ' ');
		replace_char(bag->splited_pipe[i], '\a', '>');
		replace_char(bag->splited_pipe[i], '\n', '<');
		i++;
	}
	fix_matrix(&bag->cmds);
	print_node(bag);
	free_all(bag);
	//token_free(&bag->cmds);
	//so damos free na linked list envp apenas quando encerramos o programa!
	//envs_free(&bag->envs);
}
