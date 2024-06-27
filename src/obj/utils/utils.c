/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:30:13 by aprado            #+#    #+#             */
/*   Updated: 2024/06/25 11:23:45 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_cmd(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] && (arr[i][0] == '<' || arr[i][0] == '>'))
		i += 2;
	if (arr[i])
		return (ft_strdup(arr[i]));
	return (NULL);
}

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
	return (new);
}

int	is_there_var(char *s)
{
	int	i;
	int	onequote;
	int	check;

	i = 0;
	onequote = 0;
	check = 0;
	while (s[i])
	{
		if (s[i] == 39)
			onequote++;
		else if (s[i] == '$')
		{
			if ((onequote % 2) == 1)
			{
				if (s[i + 1] && ft_isalnum(s[i + 1]))
					check = 0;
			}
			else if (s[i + 1] && ft_isalnum(s[i + 1]))
				check = 1;
		}
		i++;
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
			i++;
		}
		i = 0;
		aux = aux->next;
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = -1;
	while (s1[++i] || s2[i])
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	copy_char_pointer(char ***dest, char **src)
{
	int i;

	i = -1;
	while (src[++i])
		(*dest)[i] = ft_strdup(src[i]);
	(*dest)[i] = NULL;
}
