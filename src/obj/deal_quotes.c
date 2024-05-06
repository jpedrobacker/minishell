/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:51:06 by aprado            #+#    #+#             */
/*   Updated: 2024/05/06 17:29:42 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	replace_char(char *s, char old, char want)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == old)
			s[i] = want;
		i++;
	}
}

int	change_pipe(char *s, int *start, int *end)
{
	int	change;
	int	i;

	change = 0;
	i = *start;
	while (i <= *end)
	{
		if (s[i] == '|')
		{
			change++;
			s[i] = '\t';
		}
		i++;
	}
	*start = 0;
	*end = 0;
	if (change == 0)
		return (0);
	return (1);
}

char	*get_quote_pos(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 34 || s[i] == 39)
			return (s + i);
			//return (ft_strdup(s + i));
		i++;
	}
	return (NULL);
}

void	change_input(char *s)
{
	int		i;
	int		start;
	int		end;
	char	c1;

	i = 0;
	start = 0;
	end = 0;
	while (s[i])
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
				ft_putstr_fd("Error quote", 2);
		}
		i++;
	}
}
