/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_in_tokens_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:35:14 by aprado            #+#    #+#             */
/*   Updated: 2024/07/04 16:35:45 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/minishell.h"

int	check_chars(char c, char *in)
{
	int	i;

	i = 0;
	while (in[i])
	{
		if (c == in[i])
			return (1);
		i++;
	}
	return (0);
}

void	count_helper(char *s, int i, int *word, int *line)
{
	int	s_len;
	int	w;
	int	l;

	w = *word;
	l = *line;
	s_len = ft_strlen(s);
	if (w != 0)
	{
		l++;
		w = 0;
	}
	if ((i + 1) < s_len && (s[i + 1] == '$' || ft_isalnum(s[i + 1])))
		w++;
	else
		l++;
	*word = w;
	*line = l;
}

int	new_line_count(char *s, char *in, int i)
{
	int	word;
	int	l;

	i = -1;
	l = 0;
	word = 0;
	while (s[++i])
	{
		if (s[i] == '$')
			count_helper(s, i, &word, &l);
		else if (check_chars(s[i], in))
		{
			if (word != 0)
			{
				l++;
				word = 0;
			}
			l++;
		}
		else
			word++;
	}
	if (word)
		l++;
	return (l);
}

int	check_specials(char *s, int i, int t, char *in)
{
	int	x;
	int	s_len;

	x = 0;
	s_len = ft_strlen(s);
	if ((i + 1) < s_len)
	{
		if (s[i] == '$' && ft_isalpha(s[i + 1]) && t == 0)
			return (0);
	}
	while (in[x])
	{
		if (s[i] == in[x])
			return (1);
		x++;
	}
	return (0);
}
