/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_redirects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprado <aprado@student.42.rio>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:02:14 by aprado            #+#    #+#             */
/*   Updated: 2024/07/04 17:23:41 by aprado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// ---------------------------------------------------------------
// arquivo totalmente desnecessario :D
// ---------------------------------------------------------------

int	deal_redirects(t_main *bag)
{
	int		i;
	char	**s;

	i = 0;
	if (!bag->dup_usr_input)
		return (0);
	bag->splited_input = split_in_tokens(bag->dup_usr_input, "\"' $\v\t\n\a<>|", bag->envs);
	s = bag->splited_input;
	//PRINT DA SPLIT IN TOKENS!!!
	while (s[i])
	{
		ft_printf("splited :%s: \n", s[i]);
		i++;
	}
	return (1);
}
