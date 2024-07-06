/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_in_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:16:13 by aprado            #+#    #+#             */
/*   Updated: 2024/07/05 14:17:48 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
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

int	new_line_count(char *s, char *in)
{
	int	i;
	int	word;
	int	l;

	i = 0;
	l = 0;
	word = 0;
	while (s[i])
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
		i++;
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
*/

static void	core(char *s, char *in, int len, char ***new)
{
	int	t;
	int	j;
	int	i;

	i = -1;
	j = 0;
	t = 0;
	while (s[++i])
	{
		if (!check_specials(s, i, t, in))
			t++;
		else
		{
			if (t != 0)
			{
				(*new)[j++] = ft_substr(s, (i - t), t);
				t = 0;
				i--;
			}
			else
				(*new)[j++] = ft_substr(s, i, 1);
		}
		if (t && ((i + 1) == len))
			(*new)[j++] = ft_substr(s, ((i + 1) - t), t);
	}
}

char	**split_in_tokens(char *s, char *in, t_varenv *envs)
{
	int		lines_s;
	int		len;
	char	**new;

	len = ft_strlen(s);
	lines_s = new_line_count(s, in, -1);
	ft_printf("lines_s -> :%i:\n", lines_s);
	new = malloc(sizeof(char *) * (lines_s + 1));
	if (!new)
		return (NULL);
	new[lines_s] = NULL;
	core(s, in, len, &new);
	new_expand_envs(&new, envs);
	return (new);
}

/*
char	**split_in_tokens(char *s, char *in, t_varenv *envs)
{
	int		i;
	int		lines_s;
	int		len;
	char	**new;

	i = 0;
	len = ft_strlen(s);
	lines_s = new_line_count(s, in);
	ft_printf("lines_s -> :%i:\n", lines_s);
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
				new[j] = ft_substr(s, (i - t), t);
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
	core(s, in, len, &new);
	new_expand_envs(&new, envs);
	return (new);
}
*/

/*
// -----------------------------------------------------------------
// ESTA FUNCIONANDO. MAS NAO ESTA NA NORMA...
// -----------------------------------------------------------------
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

int	new_line_count(char *s, char *in)
{
	int	i;
	int	word;
	int	l;

	i = 0;
	l = 0;
	word = 0;
	while (s[i])
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
		i++;
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

char	**split_in_tokens(char *s, char *in, t_varenv *envs)
{
	int		i;
	int		lines_s;
	int		len;
	char	**new;

	i = 0;
	len = ft_strlen(s);
	lines_s = new_line_count(s, in);
	ft_printf("lines_s -> :%i:\n", lines_s);
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
				new[j] = ft_substr(s, (i - t), t);
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
	new_expand_envs(&new, envs);
	return (new);
}
*/
