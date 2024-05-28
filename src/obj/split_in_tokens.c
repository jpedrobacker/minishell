/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_in_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:16:13 by aprado            #+#    #+#             */
/*   Updated: 2024/05/28 13:53:49 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_char(char *s, int i, int s_len, char *in)
{
	int	x;

	x = 0;
	if ((i + 1) < s_len)
	{
		if (s[i] == '$' && ft_isalpha(s[i + 1]))
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

//echo "OLA 42 $USER rio '$HOME' $ MAIL"
//echo '$ HOME'
//'a'
int	line_count(char *s, char *in, int s_len)
{
	int	i;
	int	line_s;
	int	word;

	i = 0;
	line_s = 0;
	word = 0;
	while (s[i])
	{
		if (check_char(s, i, s_len, in))
		{
			if (word != 0)
			{
				line_s++;
				word = 0;
			}
			line_s++;
		}
		else
			word++;
		i++;
	}
	if (word)
		line_s++;
	return (line_s);
}

//echo '$HOME'
//echo
//
//usar a *ft_substr(string base, onde comecar a copiar a string base, quantos caracteres voce quer copiar)
char	**split_in_tokens(char *s, char *in, t_varenv *envs)
{
	int		i;
	int		s_len;
	int		lines_s;
	//int		line_len;
	char	**new;

	i = 0;
	//line_len = 0;
	s_len = ft_strlen(s);
	lines_s = line_count(s, in, s_len);
	ft_printf("lines_s -> :%i:\n", lines_s);
	new = malloc(sizeof(char *) * (lines_s + 1));
	if (!new)
		return (NULL);
	new[lines_s] = NULL;
	int t = 0;
	int j = 0;
	while (s[i])
	{
		if (!check_char(s, i, s_len, in))
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
		if (t && ((i + 1) == s_len))
		{
			new[j] = ft_substr(s, ((i + 1) - t), t);
			j++;
		}
		i++;
	}
	//mandar o endereço da minha matriz para uma func que vai expandir, caso precise, as envs.
	expand_envs(&new, envs);
	return (new);
}

