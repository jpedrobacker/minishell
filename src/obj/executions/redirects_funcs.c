/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_funcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:03:53 by aprado            #+#    #+#             */
/*   Updated: 2024/06/27 10:45:37 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	special(char c, char *in)
{
	int	i;

	i = 0;
	while (in[i])
	{
		if (in[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ordering_fds(t_main *bag)
{
	t_token	*aux;

	aux = bag->cmds;
	while (aux)
	{
		ft_printf("----- changing FDs -----\n");
		exec_redirects(aux, bag);
		aux = aux->next;
	}
	return (1);
}

int	is_appendoc(char *s, int *i, char c)
{
	int	len;

	len = ft_strlen(s);
	if ((*i + 1) < len)
	{
		if (s[*i + 1] == c)
		{
			(*i)++;
			while (s[*i])
			{
				if (s[*i] == ' ')
					(*i)++;
				else
					break ;
			}
			if (s[*i] == '\0' || !special(s[*i], "<>"))
				return (0);
			else
				return (1);
		}
			return (0);
	}
	return (0);
}

void	exec_redirects(t_token *node, t_main *bag)
{
	int	i;

	i = 0;
	while (node->arr[i])
	{
		if (node->arr[i][0] == '<')
		{
			if (!ft_strncmp(node->arr[i], "<<", 2))
				node->hd_fd = heredoc_func(node, bag, i);
			else
				redirect_in(node, bag, i);
		}
		else if (node->arr[i][0] == '>')
		{
			if (!ft_strncmp(node->arr[i], ">>", 2))
				append_func(node, bag, i);
			else
				redirect_out(node, bag, i);
		}
		i++;
	}
}
