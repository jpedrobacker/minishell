/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_funcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:03:53 by aprado            #+#    #+#             */
/*   Updated: 2024/06/20 15:06:57 by aprado           ###   ########.fr       */
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

static int	check_rin_rout(char *s, int *i)
{
	int	x;
	int	j;

	x = *i + 1;
	j = *i;
	while (s[x])
	{
		if (s[x] == '|' || s[x] == '<' || s[x] == '>')
			break ;
		x++;
	}
	//if (s[x] == '\0')
	//	return (1);
	if (!check_middle(s, j, x))
		return (0);
	return (1);
	/*
	if ((*i + 1) < len)
	{
		//(*i)++;
		while (s[*i])
		{
			if (s[*i] == ' ')
				(*i)++;
			else
				break ;
		}
		if (s[*i] == '\0' || !special(s[*i], "<>|"))
			return (0);
		else
			return (1);
	}
	return (0);
	*/
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
			return (check_rin_rout(s, i));
	}
	return (0);
}

void	exec_redirects(t_token *node)
{
	int		i;
	char	*temp;

	i = 0;
	temp = ft_strdup(node->token);
	change_input(temp);
	while (temp[i])
	{
		if (temp[i] == '<')
		{
			if (is_appendoc(temp, &i, temp[i]))
				ft_printf("Exec heredoc!\n"); // Func to open/create file and change FDS
			else
				ft_printf("Exec infile!\n"); // Func to open/create file and chande FDS
		}
		else if (temp[i] == '>')
		{
			if (is_appendoc(temp, &i, temp[i]))
				ft_printf("Exec append!\n"); // Func to open/create file and change FDS
			else
				ft_printf("Exec outfile!\n"); // Func to open/create file and change FDS
		}
		i++;
	}
	free(temp);
}

/*
void	check_redirects(t_main *bag)
{
	t_token *aux;

	aux = bag->cmds;
	while (aux)
	{
		exec_redirects(aux);
		aux = aux->next;
	}
}
*/
