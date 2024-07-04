/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:05:31 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/04 12:20:11 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	built_clear(t_token *token)
{
	int	i;

	i = count_cmds(token->args);
	if (i == 1)
	{
		ft_printf("%s"CLEAR);
		return (0);
	}
	return (1);
}
