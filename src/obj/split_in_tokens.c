/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_in_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:16:13 by aprado            #+#    #+#             */
/*   Updated: 2024/07/12 14:49:06 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	new = malloc(sizeof(char *) * (lines_s + 1));
	if (!new)
		return (NULL);
	new[lines_s] = NULL;
	core(s, in, len, &new);
	new_expand_envs(&new, envs);
	return (new);
}
