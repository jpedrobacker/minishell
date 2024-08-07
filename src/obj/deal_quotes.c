/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:51:06 by aprado            #+#    #+#             */
/*   Updated: 2024/07/12 14:47:00 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	change_reds(char *s, int *start, int *end)
{
	int	i;

	i = *start;
	while (i <= *end)
	{
		if (s[i] == '<')
			s[i] = '\n';
		else if (s[i] == '>')
			s[i] = '\a';
		i++;
	}
}

void	change_spaces(char *s, int *start, int *end)
{
	int	i;

	i = *start;
	while (i <= *end)
	{
		if (s[i] == ' ')
			s[i] = '\v';
		i++;
	}
}

void	change_pipe(char *s, int *start, int *end)
{
	int	i;

	i = *start;
	while (i <= *end)
	{
		if (s[i] == '|')
			s[i] = '\t';
		i++;
	}
	change_spaces(s, start, end);
	change_reds(s, start, end);
	*start = 0;
	*end = 0;
}

char	*get_quote_pos(char *s)
{
	char	*temp;

	temp = s;
	while (*temp)
	{
		if (*temp == 34 || *temp == 39)
			return (temp);
		temp++;
	}
	return (NULL);
}

int	change_input(char *s)
{
	int		i;
	int		start;
	int		end;
	char	c1;

	i = -1;
	start = 0;
	end = 0;
	while (s[++i])
	{
		if (s[i] == 34 || s[i] == 39)
		{
			c1 = s[i];
			start = i;
			i++;
			while (s[i] && s[i] != c1)
				i++;
			end = i;
			if (s[end] != '\0')
				change_pipe(s, &start, &end);
			else
				return (0);
		}
	}
	return (1);
}
