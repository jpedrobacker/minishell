/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_redirects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:02:14 by aprado            #+#    #+#             */
/*   Updated: 2024/07/12 14:51:32 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	deal_redirects(t_main *bag)
{
	if (!bag->dup_usr_input)
		return (0);
	bag->splited_input = split_in_tokens(bag->dup_usr_input,
			"\"' $\v\t\n\a<>|", bag->envs);
	return (1);
}
