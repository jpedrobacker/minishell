/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_funcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:03:53 by aprado            #+#    #+#             */
/*   Updated: 2024/06/23 16:59:40 by aprado           ###   ########.fr       */
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


/*
//FUNCAO QUE VAI ABRIR/CRIAR OS ARQUIVOS E TROCAR OS FDS NECESSARIOS
//CASO DE MERDA, VAI DAR FREE NA LINKED LIST DA ENVP E DOS CMDS
void	r_in_fd(t_token *node, t_main *bag)
{
	//abrir/criar o arquivo especifico
	//caso de certo, pegue esse novo fd, e troque pelo stdin ou stdout
	
	int	i;

	i = 0;
	while (node->arr[i])
	{
		if (node->arr[i][0] == '<')

		i++;
	}
}
*/

//VAI PRECISAR PERCORRER A MATRIZ DO NODE!!
void	exec_redirects(t_token *node, t_main *bag)
{
	int		i;
	char	**temp;

	(void)bag;
	i = 0;
	temp = node->arr;
	ft_printf("-> :%s: \n", node->token);
	while (temp[i])
	{
		if (temp[i][0] == '<')
		{
			if (!ft_strncmp(temp[i], "<<", 2))
			{
				heredoc_func(node, bag, i);
				ft_printf("Exec heredoc!\n");
			}
			else
			{
				redirect_in(node, bag, i);
				ft_printf("Exec infile!\n");
			}
		}
		else if (temp[i][0] == '>')
		{
			if (!ft_strncmp(temp[i], ">>", 2))
			{
				append_func(node, bag, i);
				ft_printf("Exec append!\n"); // Func to open/create file and change FDS
			}
			else
			{
				redirect_out(node, bag, i);
				ft_printf("Exec outfile!\n"); // Func to open/create file and change FDS
			}
		}
		i++;
	}
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
