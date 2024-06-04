/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:51:06 by aprado            #+#    #+#             */
/*   Updated: 2024/06/03 15:27:52 by aprado           ###   ########.fr       */
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

void	change_input(char *s)
{
	int		i;
	int		start;
	int		end;
	//int		len;
	char	c1;

	i = 0;
	start = 0;
	end = 0;
	while (s[i])
	{
		if (s[i] == 34 || s[i] == 39)
		{
			/*
			//TESTING
			c1 = s[i];
			start = i;
			while (s[i])
			{
				i++;
				if (s[i] && s[i] == c1)
					break ;
			}
			end = i;
			if (s[end] != '\0')
				change_pipe(s, &start, &end);
			else
				ft_putstr_fd("ERROR QUOTE>\n", 2);
			*/
			// CODIGO FUNCIONANDO, MAS COM UM ERRO NO VALGRIND.
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
		//ft_printf("OPA I -> %i\n", i);
		//if (i == (len - 1))
		//	break ;
		i++;
	}
}
