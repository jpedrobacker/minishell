/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_input_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:11:54 by aprado            #+#    #+#             */
/*   Updated: 2024/06/05 17:32:48 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	check_middle(char *s, int b, int e)
{
	int	c;

	c = 0;
	if (!s)
		return (0);
	b++;
	while (b < e)
	{
		if (s[b] != ' ' && s[b] != '\t' && s[b] != '\v')
			c++;
		if (c != 0)
			return (1);
		b++;
	}
	return (0);
}

int	check_invalid_pipe(char *s)
{
	int	i;
	int	x;

	i = 0;
	while (s[i])
	{
		x = 0;
		if (s[i] == '|')
		{
			x = i + 1;
			while (s[x])
			{
				if (s[x] == '|')
					break ;
				x++;
			}
			if (s[x] == '\0')
				return (1);
			else if (!check_middle(s, i, x))
				return (0);
		}
		i++;
	}
	return (1);
}
