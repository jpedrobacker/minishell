/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:13:15 by aprado            #+#    #+#             */
/*   Updated: 2024/07/12 14:44:53 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	flag_heredoc(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i][0] == '<')
		{
			if (ft_strlen(s[i]) == 2)
				return (1);
		}
		i++;
	}
	return (0);
}

static void	populate_nodes(t_token **node)
{
	(*node)->fd_in = STDIN_FILENO;
	(*node)->fd_out = STDOUT_FILENO;
	(*node)->hd_fd = 0;
	(*node)->pipe_in = 0;
	(*node)->pipe_out = 0;
	(*node)->pid = 0;
	(*node)->hd = flag_heredoc((*node)->arr);
}

void	create_token(char *s, t_token **head, t_main *bag)
{
	t_token	*new;
	t_token	*current;

	new = malloc(sizeof(t_token));
	if (!new)
		return (ft_putstr_fd("ERROR\n", 2));
	new->arr = ft_split(s, ' ');
	new->cmd = get_cmd(new->arr);
	new->args = get_args(new->arr);
	new->token = s;
	new->real_path = get_real_path(&bag->paths, new->cmd);
	new->next = NULL;
	populate_nodes(&new);
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
}
