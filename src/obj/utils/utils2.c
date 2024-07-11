/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 10:10:30 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/11 10:20:23 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	int	i;

	i = -1;
	while (src[++i])
		(*dest)[i] = ft_strdup(src[i]);
	(*dest)[i] = NULL;
}

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

int	ft_isvar(char c)
{
	if (c == '?')
		return (1);
	if (ft_isalnum(c))
		return (1);
	return (0);
}
