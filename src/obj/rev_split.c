/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:07:19 by aprado            #+#    #+#             */
/*   Updated: 2024/05/31 16:19:03 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	total_len(char **matrix)
{
	int	i;
	int	len;
	int	x;

	i = 0;
	len = 0;
	while (matrix[i])
	{
		x = 0;
		while (matrix[i][x])
		{
			x++;
			len++;
		}
		i++;
	}
	return (len);
}

char	*rev_split(char **matrix)
{
	int		i;
	int		x;
	int		j;
	int		len;
	char	*new;

	i = 0;
	j = 0;
	len = total_len(matrix);
	new = malloc(sizeof(char) * (len + 1));
	new[len] = '\0';
	while (matrix[i])
	{
		x = 0;
		while (matrix[i][x])
		{
			new[j] = matrix[i][x];
			j++;
			x++;
		}
		i++;
	}
	return (new);
}
