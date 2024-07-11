/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:30:13 by aprado            #+#    #+#             */
/*   Updated: 2024/07/11 10:20:28 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	count_args(char **arr)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (arr[i])
	{
		if (arr[i][0] == '<' || arr[i][0] == '>')
			i += 2;
		if (arr[i] && arr[i][0] != '<' && arr[i][0] != '>')
		{
			word++;
			i++;
		}
	}
	return (word);
}

static void	fix_args(char ***args)
{
	int	i;

	i = 0;
	while ((*args)[i])
	{
		replace_char((*args)[i], '\t', '|');
		replace_char((*args)[i], '\v', ' ');
		replace_char((*args)[i], '\n', '<');
		replace_char((*args)[i], '\a', '>');
		i++;
	}
}

char	**get_args(char **arr)
{
	int		i;
	int		x;
	int		words;
	char	**new;

	i = 0;
	x = 0;
	words = count_args(arr);
	new = malloc(sizeof(char *) * (words + 1));
	if (!new)
		return (NULL);
	new[words] = NULL;
	while (arr[i])
	{
		if (arr[i][0] == '<' || arr[i][0] == '>')
			i += 2;
		if (arr[i] && arr[i][0] != '<' && arr[i][0] != '>')
		{
			new[x] = ft_strdup(arr[i]);
			x++;
			i++;
		}
	}
	fix_args(&new);
	return (new);
}

int	is_there_var(char *s)
{
	int	i;
	int	onequote;
	int	check;

	i = -1;
	onequote = 0;
	check = 0;
	while (s[++i])
	{
		if (s[i] == 39)
			onequote++;
		else if (s[i] == '$')
		{
			if ((onequote % 2) == 1)
			{
				if (s[i + 1] && ft_isvar(s[i + 1]))
					check = 0;
			}
			else if (s[i + 1] && ft_isvar(s[i + 1]))
				check = 1;
		}
	}
	if (check)
		return (1);
	return (0);
}

void	fix_matrix(t_token **head)
{
	t_token	*aux;
	int		i;

	i = 0;
	aux = *head;
	while (aux)
	{
		while (aux->arr[i])
		{
			replace_char(aux->arr[i], '\v', ' ');
			replace_char(aux->arr[i], '\t', '|');
			replace_char(aux->arr[i], '\a', '>');
			replace_char(aux->arr[i], '\n', '<');
			i++;
		}
		i = 0;
		aux = aux->next;
	}
}
