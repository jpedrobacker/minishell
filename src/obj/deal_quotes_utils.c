/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_quotes_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:24:39 by aprado            #+#    #+#             */
/*   Updated: 2024/07/04 17:25:03 by aprado           ###   ########.fr       */
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
