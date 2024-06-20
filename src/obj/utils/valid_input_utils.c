/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_input_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:11:54 by aprado            #+#    #+#             */
/*   Updated: 2024/06/20 13:50:41 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_middle(char *s, int b, int e)
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
	int		i;
	int		x;
	char	*dup;

	i = 0;
	dup = ft_strdup(s);
	change_input(dup);
	while (dup[i])
	{
		x = 0;
		if (dup[i] == '|')
		{
			x = i + 1;
			while (dup[x])
			{
				if (dup[x] == '|')
					break ;
				x++;
			}
			if (dup[x] == '\0')
				return (free(dup), 1);
			else if (!check_middle(dup, i, x))
				return (free(dup), 0);
		}
		i++;
	}
	free(dup);
	return (1);
}

int	check_invalid_redirects(char *s)
{
	//int		x;
	int		i;
	char	*dup;

	dup = ft_strdup(s);
	change_input(dup);
	i = 0;
	while (dup[i])
	{
		//x = 0;
		if (dup[i] == '<')
		{
			if (!is_appendoc(dup, &i, dup[i]))
				return (free(dup), 0);
			/*
			x = i + 1;
			while (dup[x])
			{
				if (dup[x] == '|' || dup[x] == '>')
					break ;
				x++;
			}
			if (dup[x] == '\0')
				return (free(dup), 1);
			else if (!check_middle(dup, i, x))
				return (free(dup), 0);
			*/
		}
		else if (dup[i] == '>')
		{
			if (!is_appendoc(dup, &i, dup[i]))
				return (free(dup), 0);
			/*
			x = i + 1;
			while (dup[x])
			{
				if (dup[x] == '|' || dup[x] == '>')
					break ;
				x++;
			}
			if (dup[x] == '\0')
				return (free(dup), 1);
			else if (!check_middle(dup, i, x))
				return (free(dup), 0);
			*/
		}
		i++;
	}
	ft_printf("redirects :%s: \n", dup);
	return (free(dup), 1);
}

/*
char	**split_to_validate(char *s, char *in)
{
	int		i;
	int		lines_s;
	int		len;
	char	**new;

	i = 0;
	len = ft_strlen(s);
	lines_s = new_line_count(s, in);
	new = malloc(sizeof(char *) * (lines_s + 1));
	if (!new)
		return (NULL);
	new[lines_s] = NULL;
	int t = 0;
	int j = 0;
	while (s[i])
	{
		if (!check_specials(s, i, t, in))
			t++;
		else
		{
			if (t != 0)
			{
				new[j] = ft_substr(s, (i - t), t); //implementar free caso de merda.
				j++;
				t = 0;
				i--;
			}
			else
			{
				new[j] = ft_substr(s, i, 1);
				j++;
			}
		}
		if (t && ((i + 1) == len))
		{
			new[j] = ft_substr(s, ((i + 1) - t), t);
			j++;
		}
		i++;
	}
	return (new);
}
*/
/*
//echo << asdd echo_arg
//echo < file echo_arg
//echo > file echo_arg
//echo >> adad echo_arg
int	check_redirects(char *s)
{
	return (1);
}
*/
