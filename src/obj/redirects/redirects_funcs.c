/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_funcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:03:53 by aprado            #+#    #+#             */
/*   Updated: 2024/07/11 13:54:27 by aprado           ###   ########.fr       */
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
		if (!exec_redirects(aux, bag))
			return (0);
		ft_printf("in: %i, out: %i, hd: %i\n",
			aux->fd_in, aux->fd_out, aux->hd_fd);
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

static void	exec_redis_helper(t_token **node, t_main *bag, int i, char c)
{
	if (c == '<')
	{
		if ((*node)->fd_in != 0)
			close((*node)->fd_in);
		if (!ft_strncmp((*node)->arr[i], "<<", 2))
			(*node)->fd_in = heredoc_func((*node), bag, i);
		else
			(*node)->fd_in = redirect_in((*node), bag, i);
	}
	else if (c == '>')
	{
		if ((*node)->fd_out != 1)
			close((*node)->fd_out);
		if (!ft_strncmp((*node)->arr[i], ">>", 2))
			(*node)->fd_out = append_func((*node), bag, i);
		else
			(*node)->fd_out = redirect_out((*node), bag, i);
	}
}

int	exec_redirects(t_token *node, t_main *bag)
{
	int	i;

	i = -1;
	while (node->arr[++i])
	{
		if (node->arr[i][0] == '<')
			exec_redis_helper(&node, bag, i, '<');
		else if (node->arr[i][0] == '>')
			exec_redis_helper(&node, bag, i, '>');
		if (node->fd_in == -1 || node->fd_out == -1)
			return (0);
	}
	return (1);
}

/*
int	exec_redirects(t_token *node, t_main *bag)
{
	int	i;

	i = -1;
	while (node->arr[++i])
	{
		if (node->arr[i][0] == '<')
		{
			if (node->fd_in != 0)
				close(node->fd_in);
			if (!ft_strncmp(node->arr[i], "<<", 2))
				node->fd_in = heredoc_func(node, bag, i);
			else
				node->fd_in = redirect_in(node, bag, i);
		}
		else if (node->arr[i][0] == '>')
		{
			if (node->fd_out != 1)
				close(node->fd_out);
			if (!ft_strncmp(node->arr[i], ">>", 2))
				node->fd_out = append_func(node, bag, i);
			else
				node->fd_out = redirect_out(node, bag, i);
		}
		if (node->fd_in == -1 || node->fd_out == -1)
			return (0);
	}
	return (1);
}
*/
